#ifndef BATTLE_H_
#define BATTLE_H_

#include <string>
#include <vector>

class Territory;

class Battle {

  public:
  	
    static std::vector<int> Dice(int num_dice);
    static void SingleBattle(Territory *attacking, Territory *defending);
    static int AttackHandler(Territory *attacking, Territory *defending);
    static void SingleAttack(Territory *attacking, Territory *defending);  
    static void Capture(Territory* attacking, Territory* defending);
    static int DetermineAtkDice(Territory *attacking);
    static int DetermineDefDice(Territory *defending);
    static void DecrementUnits(Territory* territory);
};

#endif
