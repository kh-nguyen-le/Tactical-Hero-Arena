#ifndef HERO_DTO_HPP
#define HERO_DTO_HPP

#include <list>

#include "attribute.hpp"
#include "skill.hpp"
#include "heroinfo.hpp"

struct Hero_dto {
  string name;
  Attribute stats;
  list<Skill> skills;
  HeroClass heroClass;
};

ostream& operator<<(ostream& os, const Hero_dto dto);

#endif