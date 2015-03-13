#include "comp_player.h"
#include "player.h"
#include <iostream>
#include "map.h"
#include "battle.h"
#include "strategy_aggressive.h"
#include <stdlib.h> // rand(), need to find how to seed
#include <vector>

CompPlayer::CompPlayer() : Player() {
	strategy = new Aggressive();
}

void CompPlayer::Reinforce() {
	std::cout << "\nReinforcement phase:" << std::endl;
	CalculateReinforcements();

	// pick a territory
	Map::Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size()];

	// put all reinforcements there
	to_reinforce->set_num_units(to_reinforce->get_num_units() + reinforcements);
	std::cout << reinforcements << " armies have been added to " << to_reinforce->get_name() << std::endl;
}

void CompPlayer::Attack() {
	std::cout << "\nAttack phase:" << std::endl;
	this->strategy->execute(this);
}

void CompPlayer::Fortify() {
	std::cout << "\nFortification phase:" << std::endl;
	// decide between fortifying or not
	if (!WillFortify()) {
		std::cout << "CompPlayer " << this->get_id() << " chose not to fortify" << std::endl;
		return;
	}

	// pick from where
	Map::Territory *move_from = ChoosePointOfDepart();
	if (move_from == NULL)
		return;

	// pick to where
	Map::Territory *move_to = ChooseDestination(move_from);
	if (move_to == NULL)
		return;

	// move everything there
	int armies = std::rand() % (move_from->get_num_units() - 1) + 1;
	move_from->set_num_units(move_from->get_num_units() - armies);
	move_to->set_num_units(move_to->get_num_units() + armies);
	std::cout << armies << " armies successfully moved from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;
}

bool CompPlayer::WillFortify(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid territory from which troops will be moved or null if no such territory is found
Map::Territory* CompPlayer::ChoosePointOfDepart(){
	std::vector <Map::Territory*> valid_points_of_depart;
	std::vector <Map::Territory*> owned_territories = this->get_owned_territories();

	// gathers all valid_points_of_depart
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanFortify())
			valid_points_of_depart.push_back(owned_territories[i]);
	}

	// doesn't fortify if there is no valid valid_points_of_depart
	if (valid_points_of_depart.size() == 0){
		std::cout << "CompPlayer " << this->get_id() << " could not fortify" << std::endl;
		return NULL;
	}

	// randomly chooses and returns one of the valid_points_of_depart
	Map::Territory* point_of_depart = valid_points_of_depart[std::rand() % valid_points_of_depart.size()];
	return point_of_depart;
}

Map::Territory* CompPlayer::ChooseDestination(Map::Territory* move_from){
	std::vector <Map::Territory*> adjacent_owned_territories = move_from->GetAdjacentOwnedTerritories(this);
	if (adjacent_owned_territories.size() == 0){
		std::cout << "CompPlayer " << this->get_id() << " wanted to fortify, but did not"
			<< " find anywhere to move his troops to!" << std::endl;
		return NULL;
	}
	Map::Territory* destination = adjacent_owned_territories[std::rand() % adjacent_owned_territories.size()];
	return destination;
}


