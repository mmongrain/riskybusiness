#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>

#include "continent.h"
#include "game.h"
#include "map.h"
#include "player.h"
#include "territory.h"

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN ===" << std::endl;

	/** check to see length of vector of players
	if(Game::Instance().get_players()->size() == 1 && std::find(Game::Instance().get_players()->begin(), Game::Instance().get_players()->end(), id))
		victory();

	if(id.owned_territories.size() == 0)
	{
		Game::Instance().get_players()->erase(Game::Instance().get_players()->begin()+(id-1));
		std::cout << "You lose, sorry." << std::endl;

	}*/

	Reinforce();
	Attack();
	if (Game::Instance().get_game_over() == true)
		return;
	Fortify();
}

int Player::player_id = 1;

void Player::DetermineContinentOwnership() {
	std::map<Continent*, int> ownership;
	for (int i = 0; i < owned_territories.size(); i++) {
		Continent *temp = owned_territories[i]->get_continent();
		if (ownership[temp]) {
			ownership[temp] = ownership[temp] + 1;
		} else {
			ownership[temp] = 1;
		}
	}
	for (auto &it : ownership) {
		if (it.first->get_territories().size() == it.second) {
			if (std::find(owned_continents.begin(), owned_continents.end(), it.first)== owned_continents.end()) {
				owned_continents.push_back(it.first);
			}
		} else {
			owned_continents.erase(std::remove(owned_continents.begin(), owned_continents.end(), it.first), owned_continents.end());
		}
	}
}

void Player::PrintOwnedTerritories() {
	for (int i = 0; i < owned_territories.size(); i++) {
		std::cout << owned_territories[i]->get_name() << " (" 
			<< owned_territories[i]->get_num_units() << ")";
		(i < owned_territories.size() - 1) ? std::cout << ", " : std::cout << ".\n";
	}
}

void Player::CalculateReinforcements() {	
	DetermineContinentOwnership();

	// calculate the number of reinforcements
	// http://www.hasbro.com/common/instruct/risk.pdf
	// (game rules source)

	reinforcements = owned_territories.size() / 3;
	if (reinforcements < 3)
		reinforcements = 3;
	for (unsigned int i = 0; i < owned_continents.size(); i++) {
		reinforcements += owned_continents[i]->get_bonus();
	}
	// TODO: Risk Cards bonuses (?) later
}

void Player::add_continent(Continent *new_continent) {
	for (auto &continent : owned_continents) {
		if (continent == new_continent) { return; }
	}
	owned_continents.push_back(new_continent);
	NotifyObservers();
}

void Player::add_territory(Territory *new_territory) {
	for (auto &territory : owned_territories) {
		if (territory == new_territory) { return; }
	}
	owned_territories.push_back(new_territory);
	NotifyObservers();
}

void Player::remove_territory(Territory *old_territory) {
	owned_territories.erase(std::remove(owned_territories.begin(), owned_territories.end(), old_territory), owned_territories.end());
	NotifyObservers();
}

void Player::remove_continent(Continent *old_continent) {
	owned_continents.erase(std::remove(owned_continents.begin(), owned_continents.end(), old_continent), owned_continents.end());
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

void Player::set_total_units(int units) {
	this->total_units = units;
	NotifyObservers();
}

void Player::set_name(std::string name) {
	this->name = name;
	NotifyObservers();
}

// converts a string to one of the Territory objects owned by Player
// or outputs an error message and returns a null pointer
Territory* Player::StringToOwnedTerritory(std::string s) {
	Territory *territory = 0;
	for (unsigned int i = 0; i < owned_territories.size(); i++) {
		if (owned_territories[i]->get_name().compare(s) == 0) {
			territory = owned_territories[i];
			return territory;	
		}
	}
	std::cout << "You don't own this territory!" << std::endl;
	return territory;
}

// used for battles
void Player::CaptureTerritory(Territory* attacking, Territory* defending, int min, int max){

	int answer = NumConqueringArmiesToMove(min, max);

	defending->set_num_units(answer);
	attacking->set_num_units(attacking->get_num_units() - answer);
	NotifyObservers();
	defending->get_owner()->NotifyObservers();
	std::cout << answer << " armies have moved to " << defending->get_name()
		<< ", and " << attacking->get_name() << " has " << attacking->get_num_units() << " remaining" << std::endl;

	defending->get_owner()->remove_territory(defending);

	if (defending->get_owner()->get_owned_territories().size() == 0){
		Game::Instance().killPlayer(defending->get_owner());
	}
	defending->set_owner(this);
	add_territory(defending);	

	if (this->owned_territories.size() == Map::Instance().get_territories()->size()){
		Game::Instance().set_game_over(true);
	}
}
