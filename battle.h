#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>
#include "map.h"
#include "territory.h"

namespace battle {
  bool AttackIsValid(Territory* attacking, Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
  std::vector<int> Dice(int num_dice);
  int Attack(Territory* attacking, Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice);
  int AllInAttack(Territory* attacking, Territory* defending);
  int UpdateOwnership(Territory* attacking, Territory* defending, int dice, int num_units, std::string &out);
  void Battle(Territory *attacking, Territory *defending);
}

#endif
