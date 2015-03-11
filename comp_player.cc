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
	CalculateReinforcements(); 

	// pick a territory
	Map::Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size() + 1];

	// put all reinforcements there
	to_reinforce->set_num_units(to_reinforce->get_num_units() + reinforcements);

	std::cout << reinforcements << " armies have been added to " << to_reinforce->get_name() << std::endl;
}

void CompPlayer::Attack() {
	this->strategy->execute(this); 
}

void CompPlayer::Fortify() {
	// pick from where
	Map::Territory *move_from = owned_territories[std::rand() % owned_territories.size() + 1];
	Map::Territory *move_to = NULL;
	int armies;

	// pick to where
	while (move_to == NULL || move_from == move_to){
		move_to = owned_territories[std::rand() % owned_territories.size() + 1];
	}

	// move everything there
	armies = move_from->get_num_units() - 1;	
	move_from->set_num_units(move_from->get_num_units() - armies);
	move_to->set_num_units(move_to->get_num_units() + armies);
	std::cout << armies << " armies successfully moved from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;
}

// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it



