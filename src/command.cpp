#include "command.hpp"
#include <string.h>
#include <sstream>

ostream& operator<<(ostream& os, const Command& cmd){
  os << "<" << cmd.skill_index << ", <";
  for (auto lst: cmd.allied_targets) {
    os << lst << ",";
  }
  os << ">, <";
  for (auto lst: cmd.enemy_targets) {
    os << lst << ",";
  }
  os << ">";
  os << ">";
  return os;
};

istream& operator>>(istream& is, Command& cmd){
  string line;
  string target;
  stringstream ss;
  stringstream ss2;

  getline(is,line, ';');
  cmd.skill_index = stoi(line);

  getline(is,line, ';');
  ss << line;
  while (getline(ss, target, ','))
    cmd.allied_targets.push_back(target);

  getline(is,line, ';');
  ss2 << line;
  while (getline(ss2, target, ','))
    cmd.enemy_targets.push_back(target);
    
  return is;
};