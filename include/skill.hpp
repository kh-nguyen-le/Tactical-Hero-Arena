#ifndef SKILL_HPP
#define SKILL_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Target_t{
  normal,
  rng,
  all,
  lowest_hp,
  highest_atk,
  self,
};

ostream& operator<<(ostream& os, const Target_t& t);

istream& operator>>(istream& os, Target_t& t);

struct Skill{
  Skill(){}
  Skill(string i_hero, string i_name, string i_desc, int i_en, Target_t i_et,
    int i_an, Target_t i_at, int i_dmg, int i_heal, int i_cd, int i_cost)
    :hero(i_hero), name(i_name), description(i_desc), enemy_num(i_en), enemy_target(i_et),
    ally_num(i_an), ally_target(i_at), dmg_mult(i_dmg), heal_mult(i_heal), cooldown(i_cd), cost(i_cost){}

    string hero;
    string name;
    string description;
    int enemy_num;
    Target_t enemy_target;
    int ally_num;
    Target_t ally_target;
    int dmg_mult;
    int heal_mult;
    int cooldown;
    int cost;

};

istream& operator>> (istream& is, Skill& skl);

ostream& operator<<(ostream& os, const Skill& skl);

ostream& operator<<(ostream& os, const vector<Skill>& vec);


#endif