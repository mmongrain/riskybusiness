#include "battlefixtures.hh"
#include "battle.hh"
#include <stdlib.h>
#include <time.h> // time()
#include <iostream>
#include <vector>
#include <string>

int main () {
  srand(time(NULL)); // Generates a new random seed for the RNG
  battle::Country *england = new battle::Country(1, 5);
  battle::Country *france = new battle::Country(2, 5);
  std::vector<int> english_dice = battle::dice(3);
  std::vector<int> french_dice = battle::dice(2);
  std::cout << "The English army, numbering " << england->units
            << ", launches an attack on the French army, numbering "
            << france->units << "." << std::endl;
  std::string message = "boop";
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

  english_dice.clear();
  french_dice.clear();
  message.clear();
  return 0;
}
