#ifndef Hero_HPP
#define Hero_HPP
//Include simulator headers
#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
//Include other headers needed for the C++ implementation of the model
#include <limits>
#include <math.h>
#include <assert.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
//Include the relative path to the message types
#include "../data_structures/attribute.hpp"
#include "../data_structures/skill.hpp"
#include "../data_structures/skillinfo.hpp"
#include "../data_structures/heroinfo.hpp"
#include "../data_structures/event.hpp"

using namespace cadmium;
using namespace std;
//Port definition
struct Hero_ports_defs{
struct command_out : public out_port<vector<Skill>> {};
struct action_out : public out_port<Event> {};
struct stats_out : public out_port<Attribute> {};
struct command_in : public in_port<int> {};
struct action_in : public in_port<Event> {};
struct active_in : public in_port<string> {};
};
//Atomic model class
template<typename TIME> class Hero {
public:
//Ports definition
using input_ports = tuple<typename Hero_ports_defs:: command_in,
typename Hero_ports_defs:: action_in, typename Hero_ports_defs::active_in>;
using output_ports = tuple<typename Hero_ports_defs:: command_out,
typename Hero_ports_defs:: action_out, typename Hero_ports_defs::stats_out>;
//Model parameters to be overwritten during instantiation
struct state_type{
//Declare the state variables here
  string name;
  Attribute stats;
  bool active;
  bool alive;
  bool ready;
  bool acted;
  list<Skill> skills;
  HeroClass heroClass;
  unordered_map<string, int> cooldowns;
  vector<Skill> available;
  vector<Skill> last_used;
};
state_type state;
//Default constructor without parameters
Hero () noexcept{
//Define the default constructor here
  state.name = "Placeholder";
  state.stats = Attribute(100,0,0,0);
  state.active = false;
  state.alive = true;
}
//Constructor with parameters if needed
Hero(HeroInfo info) {
  state.name = info.name;
  state.stats = info.stats;
  state.active = false;
  state.alive = true;
  state.ready = false;
  state.acted = false;
  state.skills = info.skills;
  state.heroClass = info.heroClass;
  state.cooldowns = {};
  state.last_used = {};
}

void internal_transition() {
  //Define internal transition here
  if (state.active && state.acted)
  {
    for (auto& [key, value] : state.cooldowns)
    {
      if (--value == 0)
      {
        state.cooldowns.erase(key);
      }
    }
    if (state.last_used[0].cooldown > 0) {
      state.cooldowns.emplace(state.last_used[0].name, state.last_used[0].cooldown);
    }
    state.active = false;
    state.last_used.clear();
  }else if (state.active && !state.ready) {
    state.ready = true;
  }
  
}
void external_transition(TIME e, typename make_message_bags<input_ports>::type mbs){
  //Define external transition here
  if (!state.active && !state.ready && !state.acted) {
    vector<string> bag_port_active_in;
    bag_port_active_in = get_messages<typename Hero_ports_defs::active_in>(mbs);
    if (bag_port_active_in[0].compare("active_in") == 0) {
      state.stats.energy = min(state.stats.energy + 2, state.stats.max_energy);
        copy_if(state.skills.begin(), state.skills.end(), back_inserter(state.available),
          [this](Skill s){return state.cooldowns.count(s.name) == 0 && s.cost <= state.stats.energy;});
        state.active = true;
    }
  }
  else if (state.active && state.ready && !state.acted) {
    vector<int> bag_port_command_in;
    bag_port_command_in = get_messages<typename Hero_ports_defs::command_in>(mbs);
    state.last_used.push_back(skillDB[state.heroClass * bag_port_command_in[0]]);
    state.ready = false;
    state.acted = true;
  }
}
void confluence_transition(TIME e,typename make_message_bags<input_ports>::type mbs){
  //Define confluence transition here
  //Default definition
  internal_transition();
  external_transition(TIME(), std::move(mbs));
}
typename make_message_bags<output_ports>::type output() const {
  typename make_message_bags<output_ports>::type bags;
  //Define output function here
  if (state.active && !state.ready && !state.acted) {
    vector<vector<Skill>> bag_port_command_out;
    bag_port_command_out.push_back(state.available);
    get_messages<typename Hero_ports_defs::command_out>(bags) = bag_port_command_out;
  } else if (!state.last_used.empty() && state.active && state.acted) {
    vector<Event> bag_port_action_out;
    
  }
  return bags;
}
TIME time_advance() const {
  TIME next_internal;
  //Define time advance function here
  if (state.active && !state.ready) {
    next_internal = TIME("00:00:00:010");
  } else {
    next_internal = numeric_limits<TIME>::infinity();
  }
  return next_internal;
}
friend ostringstream& operator<<(ostringstream& os, const typename Hero<TIME>::state_type& state) {
  //Define how to log the state here
  os << "<" << state.name << ", " << state.stats << ", " << state.active << ", " << state.alive << ", " << state.ready << ", "
     << state.acted << ", ";
  for (auto skl : state.skills) {
    os << "<" << skl << ">";
  }
  os << ", " << state.heroClass << ", ";
  for (auto [k,v] : state.cooldowns) { 
   os << "<" << k << ": " << v << ">";
  } 
  os << ", ";
  for (auto av : state.available)
    os << "<" << av << ">";
  os << ", ";
  for (auto lu : state.last_used)
    os << "<" << lu << ">";
  return os;
}
};
#endif //Hero_HPP