#include "comp_player.h"
#include "player.h"
#include <iostream>
#include "map.cc"
#include "battle.h"
#include <vector>

CompPlayer::CompPlayer() : Player() {
	strategy = new Aggressive();
}

void Player::Reinforce() {
	Player::Reinforce(); 
	std::cout << "Player " << id << " reinforced (computer)" << std::endl;
}

void CompPlayer::Attack() {
	this->strategy->execute(this); 
	std::cout << "Player " << Player::id << " attacked (computer)" << std::endl;
}

void Player::Move() {
	std::cout << "Player " << id << " moved (computer)" << std::endl;
}



// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it


void Aggressive::execute(CompPlayer *c_player){

	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){
		std::vector<Map::Territory*> neighbors = c_player->owned_territories[i]->get_adjacency_list();

		// iterates through adjacent territories
		for (unsigned int j = 0; j < neighbors.size(); j++){

			if (c_player->owned_territories[i]->get_owner() != neighbors[j]->get_owner()
				&& c_player->owned_territories[i]->get_units() > neighbors[j]->get_units()){				
					
				battle::AllInAttack(c_player->owned_territories[i], neighbors[j]);
			}
		}
	}
}
