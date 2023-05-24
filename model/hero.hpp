#ifndef Hero_HPP
#define Hero_HPP
//Include simulator headers
#include <cadmium/core/modeling/atomic.hpp>
//Include other headers needed for the C++ implementation of the model
#include <limits>
#include <math.h>
#include <assert.h>
#include <vector>
#include <list>
#include <unordered_map>
#include <algorithm>
//Include the relative path to the message types
#include "../include/attribute.hpp"
#include "../include/skill.hpp"
#include "../include/skillinfo.hpp"
#include "../include/heroinfo.hpp"
#include "../include/event.hpp"
#include "../include/command.hpp"
#include "../include/action.hpp"
#include "../include/herodto.hpp"

using namespace cadmium;
using namespace std;

struct HeroState{
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
  list<string> allied_targets;
  list<string> enemy_targets;
  HeroState(HeroInfo info): name(info.name), stats(info.stats), skills(info.skills), heroClass(info.heroClass) {
    this->active = false;
    this->ready = false;
    this->acted = false;
    this->alive = true;
    this->cooldowns = {};
    this->available = {};
    this->last_used = {};
    this->allied_targets = {};
    this->enemy_targets = {};
  }
};

ostream& operator<<(ostream& os, const HeroState& state) {
  //Define how to log the state here
  os << "<" << state.name << ", " << state.stats << ", " << state.active << ", " << state.alive << ", " << state.ready << ", "
     << state.acted << ", <";
  for (auto skl : state.skills) {
    os << "<" << skl << ">";
  }
  os << ">, " << state.heroClass << ", <";
  for (auto [k,v] : state.cooldowns) { 
   os << "<" << k << ": " << v << ">";
  } 
  os << ">, <";
  for (auto av : state.available)
    os << "<" << av << ">";
  os << ">, <";
  for (auto lu : state.last_used)
    os << "<" << lu << ">";
  os << ">, <";
  for (auto tgt : state.allied_targets) {
    os << "<"  << tgt << ">";
  }
  os << ">, <";
  for (auto tgt : state.enemy_targets) {
    os << "<"  << tgt << ">";
  }
  os << ">";
  os << ">";
  return os;
}

class Hero: public Atomic<HeroState> {
  public:

    Port<string> active_in;
    BigPort<Event> action_in;
    BigPort<Command> command_in;
    BigPort<vector<Skill>> command_out;
    BigPort<Action> action_out;
    BigPort<Hero_dto> stats_out;

    Hero(string id, HeroState initialState): Atomic<HeroState>(id, initialState) {
      active_in = addInPort<string>("active_in");
      action_in = addInBigPort<Event>("action_in");
      command_in = addInBigPort<Command>("command_in");
      command_out = addOutBigPort<vector<Skill>>("command_out");
      action_out = addOutBigPort<Action>("action_out");
      stats_out = addOutBigPort<Hero_dto>("stats_out");
    }

    double timeAdvance(const HeroState& state) const override {
      double time;
      if (state.active && !state.ready)
      {
        time = 10;
      }else {
        time = numeric_limits<double>::infinity();
      }
      return time;
      
    }

    void output(const HeroState& state) const override{
      if (state.active && !state.ready && !state.acted) {
        command_out->addMessage(state.available);
      } else if (!state.last_used.empty() && state.active && state.acted) {
        Action action = Action(state.last_used[0], state.allied_targets, state.enemy_targets, state.name);
        action_out->addMessage(action);
      }
    }

    void internalTransition(HeroState& state) const override {
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
        state.acted = false;
      } else if (state.active && !state.ready) {
        state.ready = true;
      }
    }

    void externalTransition(HeroState& state, double e) const override {
      if (!state.active && !state.ready && !state.acted) {
        for (const auto& m: active_in->getBag()) {
          if (m.compare("active_in") == 0) {
            state.stats.energy = min(state.stats.energy + 2, state.stats.max_energy);
            copy_if(state.skills.begin(), state.skills.end(), back_inserter(state.available),
              [state](Skill s){return state.cooldowns.count(s.name) == 0 && s.cost <= state.stats.energy;});
            state.active = true;
          }
        }
      }
      else if (state.active && state.ready && !state.acted) {
        for (const auto& m: command_in->getBag()) {
          Skill skill = skillDB[state.heroClass * m->skill_index];
          state.last_used.push_back(skill);
          state.stats.energy -= skill.cost;
          state.allied_targets = m->allied_targets;
          state.enemy_targets = m->enemy_targets;
          state.ready = false;
          state.acted = true;
        }
      }
    }
};

#endif //Hero_HPP