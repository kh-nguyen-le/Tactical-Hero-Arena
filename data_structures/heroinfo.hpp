#ifndef HERO_INFO_HPP
#define HERO_INFO_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <list>
#include <unordered_map>

#include "../data_structures/attribute.hpp"
#include "../data_structures/skill.hpp"

using namespace std;

enum HeroClass {
  druid=1,
  paladin,
  warlock,
  samurai,
  bard,
  shaman
};

struct HeroInfo
{
  HeroInfo(){}
  HeroInfo(string i_name, Attribute i_stats, list<Skill> i_skills, HeroClass i_class)
  :name(i_name), stats(i_stats), skills(i_skills), heroClass(i_class){}
  string name;
  Attribute stats;
  list<Skill> skills;
  HeroClass heroClass;
};

typedef unordered_map<int, HeroInfo> HeroDB;

extern HeroDB heroDB;

#endif