#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>
#include "map.h"

namespace battle {
  bool AttackIsValid(Map::Territory* attacking, Map::Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
  std::vector<int> Dice(int num_dice);
  int Attack(Map::Territory* attacking, Map::Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice);
  int AllInAttack(Map::Territory* attacking, Map::Territory* defending);
  int Victory(Map::Territory* attacking, Map::Territory* defending, int dice, int num_units, std::string &out);
  int Battle(Map::Territory *attacking, Map::Territory *defending);
}

#endif
