#include <string>
#include <vector>

#include "map.h"
#include "player.h"
#include "territory.h"

std::string Territory::ToString() {
  std::string out = name + "," + std::to_string(x) + "," + std::to_string(y)
                    + "," + continent->get_name() + ",";
  for (unsigned int i = 0; i < adjacency_list.size(); i++) {
    out = out + adjacency_list[i]->name; 
    if (i < adjacency_list.size() - 1) {
      out = out + ",";
    }
  }
  return out;
}

bool Territory::AreAdjacent(Territory *bordering) {
  std::string border_name = bordering->get_name();
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_name().compare(border_name)) { return true; }
  }
  return false;
}

bool Territory::AttackIsValid(Territory *defending) {
  Territory *attacking = this;
	for (unsigned int i = 0; i < Map::Instance().get_territories()->size(); i++){
		if (defending->owner == attacking->owner){
			std::cout << "You can't attack your own people!";
			return false;
		}
		else if (defending->num_units < 1) {
			std::cout << "That country is empty!";
			return false;
		}
		else if (!attacking->AreAdjacent(defending)){
			std::cout << "Those two countries are not adjacent!";
			return false;
		}
	}
  return true;
}

bool Territory::CanAttack() {
  if (this->num_units < 2) { return false; }
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() != this->owner) { return true; }
  }
  return false;
}

bool Territory::CanFortify() { 
  if (this->num_units < 2) { return false; }
  for (int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() == this->owner) { return true; }
  }
  return false;
}
  
void Territory::PrintAdjacentOwnedTerritories(Player* player) {
	std::vector<Territory*> owned = Territory::GetAdjacentOwnedTerritories(player);
	for (int i = 0; i < owned.size(); i++) {
		if (owned[i]->get_owner() == player) {
			std::cout << owned[i]->get_name() << " ("
				<< owned[i]->get_num_units() << ", Player "
				<< owned[i]->get_owner()->get_id() << ")";
			(i < owned.size() - 1) ? std::cout << ", " : std::cout << ".\n";
		}
	}
}

std::vector<Territory*> Territory::GetAdjacentOwnedTerritories(Player* player){
	std::vector<Territory*> adjacent_owned;
	for (int i = 0; i < adjacency_list.size(); i++) {
		if (adjacency_list[i]->get_owner() == player) {
			adjacent_owned.push_back(adjacency_list[i]);
		}
	}
	return adjacent_owned;
}

void Territory::PrintAttackableTerritories(Player* player) {
	std::vector<Territory*> attackable = Territory::GetAttackableTerritories(player);
	for (int i = 0; i < attackable.size(); i++) {
		if (attackable[i]->get_owner() != player) {
			std::cout << attackable[i]->get_name() << " ("
				<< attackable[i]->get_num_units() << ", Player "
				<< attackable[i]->get_owner()->get_id() << ")";
			(i < attackable.size() - 1) ? std::cout << ", " : std::cout << ".\n";
		}
	}
}

std::vector<Territory *> Territory::GetAttackableTerritories(Player* player) {
	std::vector<Territory*> attackable;
	for (int i = 0; i < adjacency_list.size(); i++) {
		if (adjacency_list[i]->get_owner() != player) {
			attackable.push_back(adjacency_list[i]);
		}
	}
	return attackable;
}


std::string Territory::set_name(std::string name) {
  std::string temp = this->name;
  this->name = name;
  NotifyObservers();
  return temp;
}

Player* Territory::set_owner(Player *owner) { 
  Player *temp = this->owner;
  this->owner = owner;
  NotifyObservers();
  return temp;
}

int Territory::set_num_units(int num_units) {
  int temp = this->num_units;
  this->num_units = num_units;
  NotifyObservers();
  return temp;
}
