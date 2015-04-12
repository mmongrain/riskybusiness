#include <string>

#include "continent.h"

std::string Continent::ToString() {
  std::string out = "";
  out = get_name() + "=" + std::to_string(get_bonus());
  return out;
}

Player* Continent::set_owner(Player *new_owner) {
  Player *temp = this->owner;
  this->owner = new_owner;
  NotifyObservers();
  return temp;
}

std::string Continent::set_name(std::string name) {
  std::string temp = this->name;
  this->name = name;
  NotifyObservers();
  return temp;
}
