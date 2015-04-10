#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>

class Territory;

namespace battle {
  //public:
    bool AttackIsValid(Territory* attacking, Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
    std::vector<int> Dice(int num_dice);
    int UpdateOwnership(Territory* attacking, Territory* defending, int dice, int num_units, std::string &out);
    void Battle(Territory *attacking, Territory *defending);
    int AttackHandler(Territory *attacking, Territory *defending);
    int AutoAttack(Territory* attacking, Territory* defending);
    void SingleAttack(Territory *attacking, Territory *defending);  
    void Capture(Territory* attacking, Territory* defending);
    void Retreat(Territory* attacking, int result);
    int DetermineAtkDice(Territory *attacking);
    int DetermineDefDice(Territory *defending);
    void DecrementUnits(Territory* territory);
}

#endif
