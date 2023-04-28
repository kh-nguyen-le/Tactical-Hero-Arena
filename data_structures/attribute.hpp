#ifndef ATTRIBUTE_HPP
#define ATTRIBUTE_HPP

#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

struct Attribute{
  Attribute(){}
  Attribute(int i_hp, int i_atk, int i_def, int i_spd)
    :base_hp(i_hp), current_hp(i_hp), max_hp(i_hp), base_attack(i_atk), attack(i_atk),
    base_defense(i_def), defense(i_def), base_speed(i_spd), speed(i_spd){
      max_energy = 10;
      energy = 2;
    }

    int base_hp;
    int current_hp;
    int max_hp;
    int base_attack;
    int attack;
    int base_defense;
    int defense;
    int base_speed;
    int speed;
    int max_energy;
    int energy;

};

istream& operator>> (istream& is, Attribute& att);

ostream& operator<<(ostream& os, const Attribute& att);

#endif