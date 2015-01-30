#include <iostream>
#include <stdlib.h> // rand()
#include <algorithm> // sort()
#include <vector>
#include "battle.hh"
#include "battlefixtures.hh"

namespace battle
{
  // Tests whether an attack is valid.
  // Returns verbose error messages as "out".
  bool attack_is_valid(Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out)
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
    } else if (!Country::are_adjacent(attacking, defending)) {
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
  std::vector<int> dice(int num_dice)
  {
    std::vector<int> out;
    if (num_dice < 1 || num_dice > 3) {
      out.push_back(-1);
      return out;
    } else {
      for (int i = 0; i < num_dice; i++)
      {
        out.push_back(std::rand() % 6 + 1);
      }
      std::sort(out.begin(), out.end(), std::greater<int>());
      return out;
    }
  }

  // Stages a single attack.
  // Returns -1 on error (call attack_is_valid() for verbose error reporting),
  // 1 if the attacking country wins, and 0 otherwise.
  int attack (Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice)
  {
    std::string message;
    if (!attack_is_valid(attacking, defending, atk_dice, def_dice, message)) {
      return -1;
    }
    for (int i = 0; i < def_dice.size() && i < atk_dice.size(); i++)
    {
      if (atk_dice[i] > def_dice[i]) {
        defending->units = defending->units - 1;
      } else {
        attacking->units = attacking->units - 1;
      }
      if (defending->units == 0) {
        return 1;
      }
    }
    return 0; 
  }

  // Triggers an all-out attack, using the maximum of dice on both sides
  // until a victor is determined.
  int all_in_attack (Country* attacking, Country* defending)
  {
    while (attacking->units > 1) {
      int num_atk_dice = 1;
      int num_def_dice = 1;
      while (attacking->units - num_atk_dice > 1 && num_atk_dice < 3) {
        ++num_atk_dice;
      }
      while (defending->units - num_def_dice > 1 && num_def_dice < 2) {
        ++num_def_dice;
      }
      std::vector<int> atk_dice = dice(num_atk_dice);
      std::vector<int> def_dice = dice(num_def_dice);
      attack(attacking, defending, atk_dice, def_dice);
    }
  }

  int victory (Country* attacking, Country* defending, int num_units) {
  }
}
