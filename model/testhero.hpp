#include <cadmium/core/modeling/coupled.hpp>
#include "../include/skill.hpp"
#include "hero.hpp"

class TestHero: public cadmium::Coupled {
  public:
  cadmium::Port<std::string> active_in;
  cadmium::BigPort<std::vector<Skill>> command_out;

  TestHero(std::string id): cadmium::Coupled(id) {
    active_in = addInPort<std::string>("active_in");
    command_out = addOutBigPort<std::vector<Skill>>("command_out");

    auto heroinfo = heroDB[druid];
    auto state = HeroState(heroinfo);

    auto hero = addComponent<Hero>(heroinfo.name, state);
    addCoupling(active_in, hero->active_in);
    addCoupling(hero->command_out, command_out);
  }

};