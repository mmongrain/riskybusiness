#include "comp_player.h"
#include "player.h"
#include <iostream>
#include "map.cc"
#include "battle.h"
#include <stdlib.h> // rand(), need to find how to seed
#include <vector>

CompPlayer::CompPlayer() : Player() {
	strategy = new Aggressive();
}

void Player::Reinforce() {
	Player::Reinforce(); 

	// pick a territory
	Map::Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size() + 1];

	// put all reinforcements there
	to_reinforce->set_num_units(Map::Territory::get_num_units() + reinforcements);

	std::cout << reinforcements << " armies have been added to " << to_reinforce->get_name() << std::endl;
}

void CompPlayer::Attack() {
	this->strategy->execute(this); 
	std::cout << "Player " << Player::id << " attacked (computer)" << std::endl;
}

void Player::Move() {

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
	move_from->set_num_units(get_num_units() - armies);
	move_to->set_num_units(get_num_units() + armies);
	std::cout << armies << " armies successfully moved from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;
}

// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it


void Aggressive::execute(CompPlayer *c_player){

	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){

		std::vector<Map::Territory*> *neighbors = c_player->owned_territories[i]->get_adjacency_list();

		// iterates through adjacent territories
		for (unsigned int j = 0; j < neighbors->size(); j++){

			if (c_player->owned_territories[i]->get_owner() != (*neighbors)[j]->get_owner()
				&& c_player->owned_territories[i]->get_num_units() > (*neighbors)[j]->get_num_units()){				
					
				battle::AllInAttack(c_player->owned_territories[i], (*neighbors)[j]);
			}
		}
	}
}
