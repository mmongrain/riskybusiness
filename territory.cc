#include <string>
#include <vector>
#include <iostream>

#include "map.h"
#include "player.h"
#include "territory.h"
#include "continent.h"

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
  for (unsigned int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_name().compare(border_name)) { return true; }
  }
  return false;
}

bool Territory::CanAttack() {
  if (this->num_units < 2) { return false; }
  for (unsigned int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() != this->owner) { return true; }
  }
  return false;
}

bool Territory::CanFortify() { 
  if (this->num_units < 2) { return false; }
  for (unsigned int i = 0; i < adjacency_list.size(); i++) {
    if (adjacency_list[i]->get_owner() == this->owner) { return true; }
  }
  return false;
}
  
std::vector<Territory*> Territory::GetAdjacentOwnedTerritories(Player* player){
	std::vector<Territory*> adjacent_owned;
	for (unsigned int i = 0; i < adjacency_list.size(); i++) {
		if (adjacency_list[i]->get_owner() == player) {
			adjacent_owned.push_back(adjacency_list[i]);
		}
	}
	return adjacent_owned;
}

std::vector<Territory *> Territory::GetAttackableTerritories(Player* player) {
	std::vector<Territory*> attackable;
	for (unsigned int i = 0; i < adjacency_list.size(); i++) {
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
