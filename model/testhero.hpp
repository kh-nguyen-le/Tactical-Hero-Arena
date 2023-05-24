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

    auto state = HeroState();
    state.name = "hero";
    state.stats = Attribute(10000, 500, 50, 75);
    state.active = false;
    state.acted = false;
    state.ready = false;
    state.alive = true;
    state.skills.push_back(skillDB[0]);
    state.skills.push_back(skillDB[1]);
    state.skills.push_back(skillDB[2]);
    state.heroClass = druid;

    auto hero = addComponent<Hero>("hero", state);
    addCoupling(active_in, hero->active_in);
    addCoupling(hero->command_out, command_out);
  }

};