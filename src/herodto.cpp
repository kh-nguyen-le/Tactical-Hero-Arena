#include "../include/herodto.hpp"
#include "../include/skill.hpp"
#include "../include/attribute.hpp"

ostream& operator<<(ostream& os, const Hero_dto dto) {
  os << "<" << dto.heroClass << ", ";
  os << dto.name << ", <";
  for (auto skl: dto.skills) {
    os << skl << ", ";
  }
  os << ">, <";
  os << dto.stats << ">";
  return os;
}