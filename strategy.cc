#include <vector>
#include <string>
#include <stdlib.h> // rand()
#include <chrono>
#include <thread>

#include "player.h"
#include "territory.h"
#include "strategy.h"
#include "ui.h"
#include "game.h"

// randomly chooses between attacking or not
bool Strategy::WillAttack(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid attacking territory or null if no such territory is found
Territory* Strategy::FromWhereToAttack(Player* player){
	std::vector <Territory*> valid_attackers;
	std::vector <Territory*> owned_territories = player->get_owned_territories();

	// gathers all valid_attackers 
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanAttack())
			valid_attackers.push_back(owned_territories[i]);
	}

	// doesn't attack if there is no valid attackers
	if (valid_attackers.size() == 0){
		UI::StatusMessage("AI Player " + std::to_string(player->get_id()) + "could not attack!");
		return NULL;
	}

	// randomly chooses and returns one of the valid_attackers
	Territory* attacking = valid_attackers[std::rand() % valid_attackers.size()];
	return attacking;
}

// randomly chooses and returns a valid target territory to be attacked
Territory* Strategy::WhomToAttack(Player* player, Territory* attacking){
	std::vector <Territory*> attackable = attacking->GetAttackableTerritories(player);
	Territory* defending = attackable[std::rand() % attackable.size()];
	return defending;
}

bool Strategy::WillFortify(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid territory from which troops will be moved or null if no such territory is found
Territory* Strategy::ChoosePointOfDepart(Player *player){
	std::vector <Territory*> valid_points_of_depart;
	std::vector <Territory*> owned_territories = player->get_owned_territories();

	// gathers all valid_points_of_depart
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanFortify())
			valid_points_of_depart.push_back(owned_territories[i]);
	}

	// doesn't fortify if there is no valid valid_points_of_depart
	if (valid_points_of_depart.size() == 0) {
		UI::StatusMessage("AI Player " + std::to_string(player->get_id()) + " could not fortify!");
		return NULL;
	}

	// randomly chooses and returns one of the valid_points_of_depart
	Territory* point_of_depart = valid_points_of_depart[std::rand() % valid_points_of_depart.size()];
	return point_of_depart;
}

Territory* Strategy::ChooseDestination(Player *player, Territory* move_from){
	std::vector <Territory*> adjacent_owned_territories = move_from->GetAdjacentOwnedTerritories(player);
	if (adjacent_owned_territories.size() == 0){
		UI::StatusMessage("CompPlayer " + std::to_string(player->get_id()) + " wanted to fortify, but did not find anywhere to move his troops to!");
		return NULL;
	}
	Territory* destination = adjacent_owned_territories[std::rand() % adjacent_owned_territories.size()];
	return destination;
}

bool Strategy::WantsToAutoAttack(){
	return true;
}

int Strategy::NumConqueringArmiesToMove(int min, int max){
	return max;
}

int Strategy::GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending) {
	int num_armies = rand() % max + min;
	return (max > num_armies) ? num_armies : max;
}

bool Strategy::AutoAttackChoice() {
	return true;
}
