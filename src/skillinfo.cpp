#include "../include/heroinfo.hpp"
#include "../include/skillinfo.hpp"

SkillDB skillDB = {
  {HeroClass::druid*3-2, Skill("Druid", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::druid*3-1, Skill("Druid", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::druid*3, Skill("Druid", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  {HeroClass::paladin*3-2, Skill("Paladin", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::paladin*3-1, Skill("Paladin", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::paladin*3, Skill("Paladin", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  {HeroClass::warlock*3-2, Skill("Warlock", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::warlock*3-1, Skill("Warlock", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::warlock*3, Skill("Warlock", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  {HeroClass::samurai*3-2, Skill("Samurai", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::samurai*3-1, Skill("Samurai", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::samurai*3, Skill("Samurai", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  {HeroClass::bard*3-2, Skill("Bard", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::bard*3-1, Skill("Bard", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::bard*3, Skill("Bard", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  {HeroClass::shaman*3-2, Skill("Shaman", "Swipe", "Deal 120\% ATK to target hero", 1, Target_t::normal, 0, Target_t::normal, 120, 0, 0, 0)},
  {HeroClass::shaman*3-1, Skill("Shaman", "Rejuvenate", "Heal 170\% ATK to 2 allies with the lowest hp", 0, Target_t::normal, 2, Target_t::lowest_hp, 0, 170, 1, 1)},
  {HeroClass::shaman*3, Skill("Shaman", "Wrath", "Deal 280\% ATK to all enemies and Heal 250\% ATK to all allies", 4, Target_t::all, 4, Target_t::all, 280, 250, 2, 4)},
  };