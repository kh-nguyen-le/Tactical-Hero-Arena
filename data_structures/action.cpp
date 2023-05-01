#include "action.hpp"

ostream& operator<<(ostream& os, const Action& act) {
  os << "<" << act.last_used << ", <";
  for (auto str: act.allied_targets) {
    os << "<" << str << ">,";
  }
  os << ", <";
  for (auto str: act.enemy_targets) {
    os << "<" << str << ">,";
  }
  os << ", " << act.source << ">";
  return os;
}

