#include "card.h"
#include <iostream>

void Card::set_owner(Player* new_owner) { 
  owner = new_owner;
}

void Card::set_territory(Territory* territory) {
  this->territory = territory;
}

void Card::set_type(std::string t){
	if (t == "Joker")
		type == JOKER;
	else if (t == "Soldier")
		type == SOLDIER;
	else if (t == "Cavalry")
		type == CAVALRY;
	else if (t == "Cannon")
		type == CANNON;
	else std::cout << "wrong card type!" << std::endl;
}

std::string Card::get_card_string() {
 switch (type) {
   case JOKER   : return "Joker";
                  break;
   case SOLDIER : return "Soldier";
                  break;
   case CAVALRY : return "Cavalry";
                  break;
   case CANNON  : return "Cannon";
                  break;
   default      : return "Error in get_card_string()";
 }
}
