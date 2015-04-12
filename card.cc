#include "card.h"
#include "exceptions.h"
void Card::set_owner(Player* new_owner) { 
  owner = new_owner;
}

void Card::set_territory(Territory* territory) {
  this->territory = territory;
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
   default      : throw new CardException();
 }
}
