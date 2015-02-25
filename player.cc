#include <iostream>
#include <vector>

#include "player.h"
#include "map.h"

Player::Player() {
  id = player_id++;
}

Player::~Player() {}

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}

int Player::player_id = 0;

void Player::add_continent(Map::Continent *new_continent) {
  for (auto &continent : owned_continents) {
    if (continent == new_continent) { return; }
  }
  owned_continents.push_back(new_continent);
  NotifyObservers();
}

void Player::add_territory(Map::Territory *new_territory) {
  for (auto &territory : owned_territories) {
    if (territory == new_territory) { return; }
  }
  owned_territories.push_back(new_territory);
  NotifyObservers();
}

void Player::set_victories(int victories) {
  this->victories = victories;
  NotifyObservers();
}

void Player::set_reinforcements(int reinforcements) {
  this->reinforcements = reinforcements;
  NotifyObservers();
}

void Player::set_units(int units) {
  this->units = units;
  NotifyObservers();
}

void Player::set_name(std::string name) {
  this->name = name;
  NotifyObservers();
}
