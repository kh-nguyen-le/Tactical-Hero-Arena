#include <cadmium/core/modeling/coupled.hpp>

#include "hero.hpp"

#include "../include/attribute.hpp"
#include "../include/skill.hpp"
#include "../include/skillinfo.hpp"
#include "../include/heroinfo.hpp"
#include "../include/event.hpp"
#include "../include/command.hpp"
#include "../include/action.hpp"
#include "../include/herodto.hpp"
#include "../include/teamcombo.hpp"

using namespace std;
using namespace cadmium;

class Team: public Coupled {
  public:
  int number;

  Team(string id, int num): Coupled(id), number(num) {
    auto combo = combos[number];
    auto it = combo.begin();

    for (int i = 0; i < 4; ++i) {
      HeroClass hclass = (HeroClass)*it;
      advance(it, 1);
      auto info = heroDB[hclass];
      auto state = HeroState(info);

      auto active_in = addInBigPort<string>("active_in_" + (i + 1));
      auto action_in = addInBigPort<Event>("action_in_" + (i + 1));
      auto command_in = addInBigPort<Command>("command_in_" + (i + 1));
      auto command_out = addOutBigPort<vector<Skill>>("command_out_" + (i + 1));
      auto action_out = addOutBigPort<Action>("action_out_" + (i + 1));
      auto stats_out = addOutBigPort<Hero_dto>("stats_out_" + (i + 1));

      auto hero = addComponent<Hero>(info.name, state);

      addCoupling(active_in, hero->active_in);
      addCoupling(action_in, hero->action_in);
      addCoupling(command_in, hero->command_in);
      addCoupling(hero->command_out, command_out);
      addCoupling(hero->action_out, action_out);
      addCoupling(hero->stats_out, stats_out);

    }
  }

};