#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>
#include "map.h"

namespace battle {
  bool AttackIsValid(Map::Territory* attacking, Map::Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
  std::vector<int> Dice(int num_dice);

 
  int UpdateOwnership(Map::Territory* attacking, Map::Territory* defending, int dice, int num_units, std::string &out);


  void Battle(Map::Territory *attacking, Map::Territory *defending);
  int AttackHandler(Map::Territory *attacking, Map::Territory *defending);
  int AutoAttack(Map::Territory* attacking, Map::Territory* defending);
  void SingleAttack(Map::Territory *attacking, Map::Territory *defending);  
  void Retreat(Map::Territory* attacking, int result);
  int DetermineAtkDice(Map::Territory *attacking);
  int DetermineDefDice(Map::Territory *defending);

  // move this to Map::Territory, it belongs there
  void DecrementUnits(Map::Territory* territory)
}

#endif
