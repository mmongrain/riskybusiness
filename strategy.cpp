#include "strategy.h"
#include "player.h"
#include "battle.h"
#include "map.cc"
#include <vector>

// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it

class Aggressive : public Strategy{
	void attack(){

		// iterates through its own terrirories
		for (int i = 0; i < Player::owned_territories.size() i++){
			std::vector<Map::Territory> neighbors = Player::owned_territories[i].get_adjacency_list();
			
			// iterates through adjacent territories
			for (int j = 0; j < neighbors.size(); j++){

				if (Player::owned_territories[i].get_owner() != neighbors[j].get_owner() 
					&& Player::owned_territories[i].get_num_units() > neighbors[j].get_num_units()){
					battle::all_in_attack(Player::owned_territories[i], neighbors[j]);
				}
			}
		}
	}
};