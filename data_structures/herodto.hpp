#ifndef HERO_DTO_HPP
#define HERO_DTO_HPP

#include <list>

#include "../data_structures/attribute.hpp"
#include "../data_structures/skill.hpp"
#include "../data_structures/heroinfo.hpp"

struct Hero_dto {
  string name;
  Attribute stats;
  list<Skill> skills;
  HeroClass heroClass;
};

#endif