#include "battlefixtures.hh"
#include "battle.hh"
#include <iostream>
#include <vector>

using namespace battle;
int main () {
	Country *england = new Country(1, 6);
	Country *france = new Country(2, 8);
  std::vector<int> english_dice = dice(3);
  std::vector<int> french_dice = dice(2);
	attack(england, france, english_dice, french_dice);
	std::cout << "Wow! I compiled!" << std::endl;
	return 0;
}
