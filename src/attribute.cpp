#include "../include/attribute.hpp"

ostream& operator<<(ostream& os, const Attribute& att) {
  os << "<" << att.base_hp << ", " << att.current_hp << ", " << att.max_hp << ", " << att.base_attack << ", "
    << att.attack << ", " << att.base_defense << ", " << att.defense << ", " << att.base_speed << ", " << att.speed << ", "
    << att.max_energy << ", " << att.energy << ">";
  return os;
}

istream& operator>>(istream& is, Attribute& att) {
  is >> att.base_hp;
  is >> att.current_hp;
  is >> att.max_hp;
  is >> att.base_attack;
  is >> att.attack;
  is >> att.base_defense;
  is >> att.defense;
  is >> att.base_speed;
  is >> att.speed;
  is >> att.max_energy;
  is >> att.energy;
  return is;
}