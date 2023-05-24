#include "../include/event.hpp"

ostream& operator<<(ostream& os, const Event evt) {
  os << "<" << evt.type << ", ";
  os << "<" << evt.amount << ", ";
  os << "<" << evt.source << ", ";
  os << "<" << evt.destination << ", ";
  os << "<" << evt.team << ">";
  return os;
}