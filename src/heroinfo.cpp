#include "../include/heroinfo.hpp"
#include "../include/skillinfo.hpp"

HeroDB heroDB = {
  {HeroClass::druid, HeroInfo("Druid", Attribute(21000,200,20,50),{skillDB[HeroClass::druid*3-2], skillDB[HeroClass::druid*3-1], skillDB[HeroClass::druid*3]}, HeroClass::druid)},
  {HeroClass::paladin, HeroInfo("Paladin", Attribute(30000,150,30,30),{skillDB[HeroClass::paladin*3-2], skillDB[HeroClass::paladin*3-1], skillDB[HeroClass::paladin*3]}, HeroClass::paladin)},
  {HeroClass::warlock, HeroInfo("Warlock", Attribute(25000,210,10,40),{skillDB[HeroClass::warlock*3-2], skillDB[HeroClass::warlock*3-1], skillDB[HeroClass::warlock*3]}, HeroClass::warlock)},
  {HeroClass::samurai, HeroInfo("Samurai", Attribute(28000,190,25,45),{skillDB[HeroClass::samurai*3-2], skillDB[HeroClass::samurai*3-1], skillDB[HeroClass::samurai*3]}, HeroClass::samurai)},
  {HeroClass::bard, HeroInfo("Bard", Attribute(23000,170,16,60),{skillDB[HeroClass::bard*3-2], skillDB[HeroClass::bard*3-1], skillDB[HeroClass::bard*3]}, HeroClass::bard)},
  {HeroClass::shaman, HeroInfo("Shaman", Attribute(24000,230,22,25),{skillDB[HeroClass::shaman*3-2], skillDB[HeroClass::shaman*3-1], skillDB[HeroClass::shaman*3]}, HeroClass::shaman)},
  };