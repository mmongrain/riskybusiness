#include "battlefixtures.h"
#include "battle.h"
#include <iostream>

using namespace battle;
int main () {
	Country *england = new Country(1, 6);
	Country *france = new Country(2, 8);
	attack(england, france, 4, 2);
	std::cout << "Wow! I compiled!" << std::endl;
	return 0;
}
