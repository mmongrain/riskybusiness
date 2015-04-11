#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>

class Territory;

class Battle {
  public:
    static bool AttackIsValid(Territory* attacking, Territory* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out);
    static std::vector<int> Dice(int num_dice);
    static int UpdateOwnership(Territory* attacking, Territory* defending, int dice, int num_units, std::string &out);
    static void SingleBattle(Territory *attacking, Territory *defending);
    static int AttackHandler(Territory *attacking, Territory *defending);
    static void SingleAttack(Territory *attacking, Territory *defending);  
    static void Capture(Territory* attacking, Territory* defending);
    static int DetermineAtkDice(Territory *attacking);
    static int DetermineDefDice(Territory *defending);
    static void DecrementUnits(Territory* territory);
};

#endif
