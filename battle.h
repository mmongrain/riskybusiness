#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>
#include "battle_fixtures.h"
#include "map.cc"

namespace battle {
  bool attack_is_valid(Map::Territory* attacking, Map::Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
  std::vector<int> dice(int num_dice);
  int attack(Map::Territory* attacking, Map::Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice);
  int all_in_attack(Map::Territory* attacking, Map::Territory* defending);
  int victory(Map::Territory* attacking, Map::Territory* defending, int dice, int num_units, std::string &out);
}

#endif
