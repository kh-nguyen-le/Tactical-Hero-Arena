#include "../include/teamcombo.hpp"

unordered_map<int, list<int>> combos = {
  {1, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::warlock, HeroClass::samurai})},
  {2, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::warlock, HeroClass::bard})},
  {3, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::warlock, HeroClass::shaman})},
  {4, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::samurai, HeroClass::bard})},
  {5, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::samurai, HeroClass::shaman})},
  {6, list<int>({HeroClass::druid, HeroClass::paladin, HeroClass::bard, HeroClass::shaman})},
  {7, list<int>({HeroClass::druid, HeroClass::warlock, HeroClass::samurai, HeroClass::bard})},
  {8, list<int>({HeroClass::druid, HeroClass::warlock, HeroClass::samurai, HeroClass::shaman})},
  {9, list<int>({HeroClass::druid, HeroClass::warlock, HeroClass::bard, HeroClass::shaman})},
  {10, list<int>({HeroClass::druid, HeroClass::samurai, HeroClass::bard, HeroClass::shaman})},
  {11, list<int>({HeroClass::paladin, HeroClass::warlock, HeroClass::samurai, HeroClass::bard})},
  {12, list<int>({HeroClass::paladin, HeroClass::warlock, HeroClass::samurai, HeroClass::shaman})},
  {13, list<int>({HeroClass::paladin, HeroClass::warlock, HeroClass::bard, HeroClass::shaman})},
  {14, list<int>({HeroClass::paladin, HeroClass::samurai, HeroClass::bard, HeroClass::shaman})},
  {15, list<int>({HeroClass::warlock, HeroClass::samurai, HeroClass::bard, HeroClass::shaman})},
};