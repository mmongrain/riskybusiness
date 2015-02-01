#include "battlefixtures.h"
#include "battle.h"
#include <stdlib.h>
#include <time.h> // time()
#include <iostream>
#include <vector>
#include <string>

namespace battle {
  // These parameters can be altered for testing
  const int english_units = 5;
  const int french_units = 3;
}

int main () {
  srand(time(NULL)); // Generates a unique-ish seed for the RNG
  battle::Country *england = new battle::Country(1, battle::english_units);
  battle::Country *france = new battle::Country(2, battle::french_units);
  int exit = 0;
  std::cout << "You are the general of the English army. After a grueling "
            << "seven days' march, your army of " << battle::english_units 
            << " battalions has reached Paris. " << battle::french_units 
            << " French battalions defend the city." << std::endl 
            << "How many units (1-3) will you send to battle? (Enter 0 for an "
            << "all-out attack, or 4 to quit.)" << std::endl;
  while (exit == 0) {
    int attackers;
    std::cin >> attackers;
    if (attackers == 4) {
      exit = 1;
      break;
    }
    if (france->units == 0)
    {
      int max_imperialists = england->units - 1 + attackers;




      std::cout << "The English army has taken Paris!" << std::endl
                << "How many battalions will it install?" << std::endl;
      int imperialists;
      std::cin >> imperialists;
      // victory(england, france, imperialists);




      exit = 1;
    }

    if (attackers > 0 && attackers < 4) {
      std::vector<int> english_dice = battle::dice(attackers);
      std::vector<int> french_dice = battle::dice((attackers >= 2) ? 2 : 1);
      std::cout << "The English army, numbering " << england->units
                << ", launches an attack on the French army, numbering "
                << france->units << "." << std::endl;
      std::string message; 
      battle::attack_is_valid(england, france, english_dice, french_dice, message);
      std::cout << message << std::endl;
      battle::attack(england, france, english_dice, french_dice);
      std::cout << "The English army rolls ";
      for (int i = 0; i < english_dice.size(); i++) {
      std::cout << english_dice[i] << " ";
      }
      std::cout << std::endl << "The French army rolls ";
      for (int i = 0; i < french_dice.size(); i++) {
        std::cout << french_dice[i] << " ";
      }
      std::cout << std::endl << "As a result, the English army now numbers "
                << england->units << " and the French army now numbers "
                << france->units << "." << std::endl;
      std::cout << "How many dice will you roll? You have "
                << england-> units << " battalions remaining." << std::endl;
    }
  }
  return 0;
}
