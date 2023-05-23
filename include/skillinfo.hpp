#ifndef SKILL_INFO_HPP
#define SKILL_INFO_HPP

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


#include "../data_structures/skill.hpp"

using namespace std;


typedef unordered_map<int, Skill> SkillDB;

extern SkillDB skillDB;

#endif