#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>
#include "battlefixtures.h"

namespace battle {
  bool attack_is_valid(Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
  std::vector<int> dice(int num_dice);
  int attack(Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice);
  int all_in_attack(Country* attacking, Country* defending);
  int victory(Country* attacking, Country* defending, int dice, int num_units, std::string &out);
}

#endif
