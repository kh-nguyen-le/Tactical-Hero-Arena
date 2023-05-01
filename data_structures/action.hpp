#ifndef ACTION_HPP
#define ACTION_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <list>
#include "skill.hpp"

using namespace std;

struct Action
{
  Action(){}
  Action(Skill lu, list<string> ally, list<string> enemy, string src)
  :last_used(lu), allied_targets(ally), enemy_targets(enemy), source(src){}

  Skill last_used;
  list<string> allied_targets;
  list<string> enemy_targets;
  string source;
};

// istream& operator>>(istream& is, Action& act);

ostream& operator<<(ostream& os, const Action& act);

#endif