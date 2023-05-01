#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <list>

using namespace std;

struct Command
{
  Command(){}
  Command(int idx, list<string> ally, list<string> enemy)
  :skill_index(idx), allied_targets(ally), enemy_targets(enemy){}

  int skill_index;
  list<string> allied_targets;
  list<string> enemy_targets;
};

istream& operator>>(istream& is, Command& cmd);

ostream& operator<<(ostream& os, const Command& cmd);

#endif