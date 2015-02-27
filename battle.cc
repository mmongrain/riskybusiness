#include <iostream>
#include <stdlib.h> // rand()
#include <algorithm> // sort()
#include <vector>
#include <time.h> // time()
#include "game.h"
#include "battle.h"
#include "map.h"

// Tests whether an attack is valid.
// Returns verbose error messages as std::string "out", which also serve to
// clarify the logic of each condition.
bool battle::AttackIsValid(Map::Territory *attacking, Map::Territory *defending, std::vector<int> atk_dice, std::vector<int> def_dice, std::string &out) {
  int current_player = 1;

  // I propose to move some of these checks to the HumanPlayer Attack method,
  // would be easier to handle each one of them. 

  if (attacking->get_owner() == defending->get_owner()) {
    out = "You can't attack your own people!";
    return false;
  } else if (attacking->get_units() < 1 || defending->get_units() < 1) {
    out = "One of those countries is empty!";
    return false;
  } else if (atk_dice.size() < 1 || atk_dice.size() > 3) {
    out = "Invalid number of attacking dice!";
    return false;
  } else if (def_dice.size() < 1 || def_dice.size() > 2) {
    out = "Invalid number of defending dice!";
    return false;
  } else if (attacking->get_owner() != Game::get_current_player()) {
    out = "Not that player's turn!";
    return false;
  } else if (attacking->get_units() - atk_dice.size() < 1) {
    out = "Attacker does not have enough units!";
    return false;
  } else if (def_dice.size() > atk_dice.size()) {
    out = "Cannot be more defenders than attackers!";
    return false;	
  } else if (!Map::Territory::AreAdjacent(attacking, defending)) {
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
std::vector<int> battle::Dice(int num_dice) {
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
int battle::Attack(Map::Territory *attacking, Map::Territory *defending, std::vector<int> atk_dice, std::vector<int> def_dice) {
  std::string message;
  if (!AttackIsValid(attacking, defending, atk_dice, def_dice, message)) {
    std::cout << message << std::endl;
    return -1;
  }
  for (int i = 0; i < def_dice.size() && i < atk_dice.size(); i++)
  {
  // If the attacker's dice is greater, decrement the number of defending units;
    if (atk_dice[i] > def_dice[i]) {
      defending->set_units(defending->get_units() - 1);
  // Otherwise decrement the number of attacking units.
    } else {
      attacking->set_units(attacking->get_units() - 1);
    }
    if (defending->get_units() == 0) {
      return 1;
    }
  }
  return 0; 
}

// Triggers an all-out attack, using the maximum of dice on both sides
// until a victor is determined.
int battle::AllInAttack (Map::Territory *attacking, Map::Territory *defending) {
  while (attacking->get_units() > 1 && defending->get_units() > 0) {
    // If there are 2 or more attacking dice, roll 2 defending dice,
    // otherwise roll 1.
    int num_def_dice = (defending->get_units() - 2 >= 0 && attacking->get_units() > 2) ? 2 : 1;
    // Then figure out how many atk_dice there can be without reducing the
    // number of units in the attacking country to below 1
    int num_atk_dice = 1;
    while (attacking->get_units() - num_atk_dice > 1 && num_atk_dice < 3) {
      ++num_atk_dice;
    }
    std::vector<int> atk_dice = Dice(num_atk_dice);
    std::vector<int> def_dice = Dice(num_def_dice);
    std::string message;
    if (AttackIsValid(attacking, defending, atk_dice, def_dice, message)) {
      Attack(attacking, defending, atk_dice, def_dice);
      std::cout << message << std::endl;
    } else { 
      std::cout << message << std::endl;
      return 0;
    }
    if (defending->get_units() == 0)
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
int battle::Victory (Map::Territory *attacking, Map::Territory *defending, int dice, int num_units, std::string &out) {
  if (defending->get_units() > 0) {
    out = "Conquered country is not empty!";
	return 0;
  } else if (attacking->get_units() - num_units < 1) {
    out = "Not enough armies in conquering country!";
    return 0;
  } else {
    out = "All OK!";
    defending->get_owner()->remove_territory(defending);
    attacking->get_owner()->add_territory(defending);
    defending->set_owner(attacking->get_owner());
    attacking->set_units(attacking->get_units() - num_units - dice);
    defending->set_units(num_units + dice);
    attacking->get_owner()->NotifyObservers();
    defending->get_owner()->NotifyObservers();
    return 1;
  }
}

// TODO: Break this monster up into subfunctions
int battle::Battle (Map::Territory *attacking, Map::Territory *defending) {
  srand(time(NULL)); // Generates a unique-ish seed for the RNG
  int winners; // Will store the number of conquering armies

  while (true) {
    // CONDITION 1: The attacking army loses.
    if (attacking->get_units() == 1 && defending->get_units() > 0) {
      std::cout << "The attacking army, humbled, retreats!" << std::endl;
      break;
    }
    
    // CONDITION 2: The defending army loses.
    if (defending->get_units() == 0) {
      int max_imperialists = attacking->get_units() - 1;
      std::cout << "The attacking army has taken " << attacking->get_name() << "!" << std::endl
                << "How many battalions (" << winners << "-"
                << max_imperialists << ") will it install?" << std::endl;
      int imperialists;
      std::cin >> imperialists;
      imperialists -= winners;
      std::string message;
      if (Victory(attacking, defending, winners, imperialists, message)) {
        std::cout << message << std::endl;
        std::cout << "After the dust settles, " << attacking->get_name() << " has " << attacking->get_units()
                  << " remaining, and the attacking army has installed "
                  << defending->get_units() << " battalions in " << defending->get_name() << std::endl;
      } else { 
        std::cout << message << std::endl; 
      } 
      break;
    }

    std::cout << "How many get_units() (1-3) will you send to battle? (Enter 4 for an "
			<< "all-out attack, or 5 to quit.)" << std::endl;
    std::cout << attacking->get_units() << "-" << defending->get_units() << ": ";
    int attackers;
    std::cin >> attackers;

    // CONDITION 3: The user quits.
    if (attackers == 5) {
      std::cout << "Bye!" << std::endl;
      break;
    }

    // CONDITION 4: The user launches an all-out attack.
    if (attackers == 4) {
      winners = AllInAttack(attacking, defending);
      std::cout << "The attacking army launches a devastating, all-in attack!!"
                << std::endl << "After the dust settles, there are "
                << attacking->get_units() << " attacking battalions and "
                << defending->get_units() << " defending battalions remaining."
                << std::endl;
    }

    // CONDITION 5: The user launches a single attack.
    if (attackers > 0 && attackers < 4) {
      std::vector<int> attack_dice = battle::Dice(attackers);
      std::vector<int> defend_dice = battle::Dice((attackers >= 2 && defending->get_units() > 1) ? 2 : 1);
      std::cout << "The attacking army, numbering " << attacking->get_units()
                << ", launches an attack on the defending army, numbering "
                << defending->get_units() << "." << std::endl;
      std::string message; 
      if (battle::AttackIsValid(attacking, defending, attack_dice, defend_dice, message)) {
        std::cout << message << std::endl;
        battle::Attack(attacking, defending, attack_dice, defend_dice);
        std::cout << "The attacking army rolls ";
        for (int i = 0; i < attack_dice.size(); i++) {
        std::cout << attack_dice[i] << " ";
        }
        std::cout << std::endl << "The defending army rolls  ";
        for (int i = 0; i < defend_dice.size(); i++) {
          std::cout << defend_dice[i] << " ";
        }
        std::cout << std::endl << "As a result, the attacking army now numbers "
                  << attacking->get_units() << " and the defending army now numbers "
                  << defending->get_units() << "." << std::endl;

      } else { 
        std::cout << message << std::endl; 
      }  
      if (defending->get_units() == 0) { 
        winners = attackers;
      }
      else if (attacking->get_units() > 1) {  
        int max_dice;
        if (attacking->get_units() == 2) { max_dice = 1; }
        else if (attacking->get_units() == 3) { max_dice = 2; }
        else { max_dice = 3; }
        std::cout << "How many dice (1-" << max_dice << ") will you roll? "
                  << attacking->get_units() << " battalions remain." << std::endl;
      }
    }
  }
}
