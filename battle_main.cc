#include "battle_fixtures.h"
#include "battle.h"
#include <stdlib.h> // srand()
#include <time.h> // time()
#include <iostream>
#include <vector>
#include <string>

namespace battle {
  // These parameters can be altered for testing.
  // These defaults result in an English victory most of the time.
  const int english_units = 5;
  const int french_units = 3;
}

int main () {
  srand(time(NULL)); // Generates a unique-ish seed for the RNG
  battle::Country *england = new battle::Country(1, battle::english_units);
  battle::Country *france = new battle::Country(2, battle::french_units);
  int winners; // Will store the number of conquering armies
  std::cout << "You are the general of the English army. After a grueling "
            << "seven days' march, your army of " << battle::english_units 
            << " battalions has reached Paris. " << battle::french_units 
            << " French battalions defend the city." << std::endl 
            << "How many units (1-3) will you send to battle? (Enter 4 for an "
            << "all-out attack, or 5 to quit.)" << std::endl;

  // This is the main loop, and has 5 primary conditions:
  while (true) {
    std::cout << england->units << "-" << france->units << ": ";

    // CONDITION 1: The English army loses.
    if (england->units == 1 && france->units > 0) {
      std::cout << "The English army, humbled at the gates of Paris, retreats!"
                << std::endl;
      break;
    }
    
    // CONDITION 2: The French army loses.
    if (france->units == 0) {
      int max_imperialists = england->units - 1;
      std::cout << "The English army has taken Paris!" << std::endl
                << "How many battalions (" << winners << "-"
                << max_imperialists << ") will it install?" << std::endl;
      int imperialists;
      std::cin >> imperialists;
      imperialists -= winners;
      std::string message;
      if (victory(england, france, winners, imperialists, message)) {
        std::cout << message << std::endl;
        std::cout << "After the dust settles, England has " << england->units
                  << " remaining, and the English army has installed "
                  << france->units << " battalions in Paris." << std::endl;
      } else { 
        std::cout << message << std::endl; 
      } 
      break;
    }

    int attackers;
    std::cin >> attackers;

    // CONDITION 3: The user quits.
    if (attackers == 5) {
      std::cout << "Bye!" << std::endl;
      break;
    }

    // CONDITION 4: The user launches an all-out attack.
    if (attackers == 4) {
      winners = all_in_attack(england, france);
      std::cout << "The English army launches a devastating, all-in attack!!"
                << std::endl << "After the dust settles, there are "
                << england->units << " English battalions and "
                << france->units << " French battalions remaining."
                << std::endl;
    }

    // CONDITION 5: The user launches a single attack.
    if (attackers > 0 && attackers < 4) {
      std::vector<int> english_dice = battle::Dice(attackers);
      std::vector<int> french_dice = battle::Dice((attackers >= 2 && france->units > 1) ? 2 : 1);
      std::cout << "The English army, numbering " << england->units
                << ", launches an attack on the French army, numbering "
                << france->units << "." << std::endl;
      std::string message; 
      if (battle::AttackIsValid(england, france, english_dice, french_dice, message)) {
        std::cout << message << std::endl;
        battle::Attack(england, france, english_dice, french_dice);
        std::cout << "The English army rolls ";
        for (int i = 0; i < english_dice.size(); i++) {
        std::cout << english_dice[i] << " ";
        }
        std::cout << std::endl << "The French army rolls  ";
        for (int i = 0; i < french_dice.size(); i++) {
          std::cout << french_dice[i] << " ";
        }
        std::cout << std::endl << "As a result, the English army now numbers "
                  << england->units << " and the French army now numbers "
                  << france->units << "." << std::endl;

      } else { 
        std::cout << message << std::endl; 
      }  
      if (france->units == 0) { 
        winners = attackers;
      }
      else if (england->units > 1) {  
        int max_dice;
        if (england->units == 2) { max_dice = 1; }
        else if (england->units == 3) { max_dice = 2; }
        else { max_dice = 3; }
        std::cout << "How many dice (1-" << max_dice << ") will you roll? "
                  << england->units << " battalions remain." << std::endl;
      }
    }
  }
  return 0;
}
