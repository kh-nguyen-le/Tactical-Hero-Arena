#include "../include/skill.hpp"

ostream& operator<<(ostream& os, const Target_t& t){
  switch(t) {
    case Target_t::normal: return os << "normal";
    case Target_t::rng: return os << "random";
    case Target_t::all: return os << "all";
    case Target_t::lowest_hp: return os << "lowest_hp";
    case Target_t::highest_atk: return os << "highest_atk";
    case Target_t::self: return os << "self";
  }
  return os;
}

istream& operator>>(istream& is, Target_t& t) {
  string input;
  is >> input;
  if (input.compare("normal") == 0 || input.compare("0")) t = Target_t::normal;
  else if (input.compare("random") == 0 || input.compare("1")) t = Target_t::rng;
  else if (input.compare("all") == 0 || input.compare("2")) t = Target_t::all;
  else if (input.compare("lowest_hp") == 0 || input.compare("3")) t = Target_t::lowest_hp;
  else if (input.compare("highest_atk") == 0 || input.compare("4")) t = Target_t::highest_atk;
  else if (input.compare("self") == 0 || input.compare("5")) t = Target_t::self;
  else {}

  return is;
}

ostream& operator<<(ostream& os, const Skill& skl){
  os << "<" << skl.hero << ", " << skl.name << ", " << skl.description << ", " << skl.enemy_num << ", "
    << skl.enemy_target << ", " << skl.ally_num << ", " << skl.ally_target << ", " << skl.dmg_mult << ", "
    << skl.heal_mult << ", " << skl.cooldown << ", " << skl.cost << ">";
  return os;
}

ostream& operator<<(ostream& os, const vector<Skill>& vec) {
  os << "[";
  for (auto skill: vec) {
    os << skill << ", ";
  }
  os << "]";
  return os;
}

istream& operator>> (istream& is, Skill& skl){
  is >> skl.hero;
  is >> skl.name;
  is >> skl.description;
  is >> skl.enemy_num;
  is >> skl.enemy_target;
  is >> skl.ally_num;
  is >> skl.ally_target;
  is >> skl.dmg_mult;
  is >> skl.heal_mult;
  is >> skl.cooldown;
  is >> skl.cost;
  return is;
}