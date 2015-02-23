#include <iostream>
#include <stdlib.h> // rand()
#include <algorithm> // sort()
#include <vector>
#include "battle.h"
#include "battle_fixtures.h"

namespace battle
{
  // Tests whether an attack is valid.
  // Returns verbose error messages as std::string "out", which also serve to
  // clarify the logic of each condition.
  bool AttackIsValid(Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out)
  {
    int current_player = 1;
    if (attacking->owner == defending->owner) {
      out = "You can't attack your own people!";
      return false;
    } else if (attacking->units < 1 || defending->units < 1) {
      out = "One of those countries is empty!";
      return false;
    } else if (atk_dice.size() < 1 || atk_dice.size() > 3) {
      out = "Invalid number of attacking dice!";
      return false;
    } else if (def_dice.size() < 1 || def_dice.size() > 2) {
      out = "Invalid number of defending dice!";
      return false;
    } else if (attacking->owner != current_player) {
      out = "Not that player's turn!";
      return false;
    } else if (attacking->units - atk_dice.size() < 1) {
      out = "Attacker does not have enough units!";
      return false;
    } else if (def_dice.size() > atk_dice.size()) {
      out = "Cannot be more defenders than attackers!";
      return false;
    } else if (!Country::AreAdjacent(attacking, defending)) {
      out = "Those two countries are not adjacent!";
      return false;
    } else {
      out = "All OK!";
      return true;
    }
  }

  // Rolls between one and three dice--no more, no less.
  // Returns a vector of up to three ints, sorted in decreasing numerical order
  // for convenience to the attack() method.
  // Deals with invalid input by returning a vector of -1.
  std::vector<int> Dice(int num_dice)
  {
    std::vector<int> out;
    if (num_dice < 1 || num_dice > 3) {
      out.push_back(-1);
      return out;
    } else {
      for (int i = 0; i < num_dice; i++)
      {
		// Generates a random int between 1 and 6.
		// Will require some kind of seed to be generated in main() for the
		// distribution to be anything close to actually random.
        out.push_back(std::rand() % 6 + 1);
      }
	  // Sorts the vector, from begin() to end(), using the > operator
      std::sort(out.begin(), out.end(), std::greater<int>());
      return out;
    }
  }

  // Stages a single attack.
  // Returns -1 on error (call AttackIsValid() for verbose error reporting),
  // 1 if the attacking country wins, and 0 otherwise.
  int Attack (Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice)
  {
    std::string message;
    if (!AttackIsValid(attacking, defending, atk_dice, def_dice, message)) {
      return -1;
    }
    for (int i = 0; i < def_dice.size() && i < atk_dice.size(); i++)
    {
	  // If the attacker's dice is greater, decrement the number of defending units;
      if (atk_dice[i] > def_dice[i]) {
        defending->units -= 1;
    // Otherwise decrement the number of attacking units.
      } else {
        attacking->units -= 1;
      }
      if (defending->units == 0) {
        return 1;
      }
    }
    return 0; 
  }

  // Triggers an all-out attack, using the maximum of dice on both sides
  // until a victor is determined.
  int AllInAttack (Country* attacking, Country* defending) 
  {
    while (attacking->units > 1 && defending->units > 0) {
      // If there are 2 or more attacking dice, roll 2 defending dice,
      // otherwise roll 1.
      int num_def_dice = (defending->units - 2 >= 0 && attacking->units > 2) ? 2 : 1;
      // Then figure out how many atk_dice there can be without reducing the
      // number of units in the attacking country to below 1
      int num_atk_dice = 1;
      while (attacking->units - num_atk_dice > 1 && num_atk_dice < 3) {
        ++num_atk_dice;
      }
      std::vector<int> atk_dice = dice(num_atk_dice);
      std::vector<int> def_dice = dice(num_def_dice);
      std::string message;
      if (AttackIsValid(attacking, defending, atk_dice, def_dice, message)) {
        attack(attacking, defending, atk_dice, def_dice);
        std::cout << message << std::endl;
      } else { 
        std::cout << message << std::endl;
        return 0;
      }
      if (defending->units == 0)
      {
        return num_atk_dice;
      }
    }
    return 0;
  }

  // Performs the actions required once a country has prevailed!
  // Most notably, by transferring the appropriate number of armies to the
  // newly conquered country.
  // Actually determining the Victory condition (i.e., that there are no units
  // remaining in the defending country and at least one unit remaining in the
  // attacking country) is left to the main() method.
  int Victory (Country* attacking, Country* defending, int dice, int num_units, std::string &out) 
  {
    if (defending->units > 0) {
      out = "Conquered country is not empty!";
      return 0;
    } else if (attacking->units - num_units < 1) {
      out = "Not enough armies in conquering country!";
      return 0;
    } else {
      out = "All OK!";
      defending->owner = attacking->owner;
      attacking->units = attacking->units - num_units - dice;
      defending->units = num_units + dice;
      return 1;
    }
  }
}
