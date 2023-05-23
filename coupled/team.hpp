#ifndef TEAM_HPP
#define TEAM_HPP

#include <cadmium/modeling/ports.hpp>
#include <cadmium/modeling/message_bag.hpp>
#include <cadmium/modeling/dynamic_coupled.hpp>
#include <cadmium/modeling/dynamic_model_translator.hpp>

#include <NDTime.hpp>

#include <limits>
#include <math.h>
#include <assert.h>

#include "../atomics/hero.hpp"
#include "../data_structures/heroinfo.hpp"
#include "../data_structures/teamcombo.hpp"
#include "../data_structures/attribute.hpp"
#include "../data_structures/skill.hpp"
#include "../data_structures/herodto.hpp"
#include "../data_structures/command.hpp"
#include "../data_structures/action.hpp"

using namespace std;
using namespace cadmium;
using namespace cadmium::basic_models::pdevs;

using TIME = NDTime;

template<typename TIME> class Team : public dynamic::modeling::coupled<TIME> {
  public:
    Team(const string& name, int num) : dynamic::modeling::coupled<TIME>(name), team_num(num) {
      list<int> heroes = combos[team_num];
      for (auto heroClass : heroes) {
        auto hero_info = heroDB[heroClass];
        auto hero_model = dynamic::translate::make_dynamic_atomic_model<Hero, TIME>(hero_info.name, hero_info);
        this->add_submodel(hero_model);
        this->template add_input_port<string>("active_in_" + hero_info.name);
        this->template add_input_port<Command>("command_in_" + hero_info.name);
        this->template add_input_port<Event>("action_in_" + hero_info.name);

        this->template add_output_port<vector<Skill>>("command_out_" + hero_info.name);
        this->template add_output_port<Action>("action_out_" + hero_info.name);
        this->template add_output_port<Hero_dto>("stats_out_" + hero_info.name);

        this->template add_coupling<string, string>("active_in", "active_in_" + hero_info.name);
        this->template add_coupling<Command, Command>("command_in", "command_in_" + hero_info.name);
        this->template add_coupling<Event, Event>("action_in", "action_in_" + hero_info.name);
        this->template add_coupling<vector<Skill>, vector<Skill>>("command_out", "command_out_" + hero_info.name);
        this->template add_coupling<Action, Action>("action_out", "action_out_" + hero_info.name);
        this->template add_coupling<Hero_dto, Hero_dto>("stats_out", "stats_out_" + hero_info.name);

      }
    }

    Team& add_submodel(shared_ptr<dynamic::modeling::model> submodel) {
      dynamic::modeling::coupled<TIME>::add_submodel(submodel);
      return *this;
    }

    template<typename U> Team& add_input_port(const string& name) {
      this->template add_input_port<U>(name);
      return *this;
    
    }
    template<typename U> Team& add_output_port(const string& name) {
      this->template add_output_port<U>(name);
      return *this;
    }

    template<typename T1, typename T2> Team& add_coupling(const string& src_port, const string& dst_port) {
        this->template coupled<TIME>::template add_coupling<T1, T2>(src_port, dst_port);
        return *this;
    }

    void initialize() {
      for (auto& submodel : this._children) {
        submodel->initialize();
      }
    }

    void external_transition(TIME e) {
      TIME next_internal;
      for (auto& submodel : this->_children) {
        next_internal = this->model().time_advance();
        submodel->external_transition(next_internal);
      }
    }

    void internal_transition() {
      for (auto& submodel : this->_children) {
        submodel->internal_transition();
      }
    }

    void output() {
      for (auto& submodel : this->_children) {
        submodel->output();
      }
    }

    friend ostringstream& operator<<(ostringstream& os, const Team<TIME>& m) {
      for (const auto& submodel : m._children) {
        os << "<> " << submodel->get_id() << "\n";
      }
      return os;
    }
  private:
    int team_num;
};

#endif