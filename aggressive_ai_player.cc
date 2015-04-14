#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "aggressive_ai_player.h"
#include "territory.h"
#include "game.h"
#include "ui.h"

class Player;

// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it

void Aggressive::Attack(Player *player){

	// iterates through its own terrirories
	for (unsigned int i = 0; i < player->get_owned_territories().size(); i++){

		std::vector<Territory*> attackable = player->get_owned_territories()[i]->GetAttackableTerritories(player);

		// iterates through adjacent territories and attacks the first valid target
		for (unsigned int j = 0; j < attackable.size(); j++){

			if (player->get_owned_territories()[i]->get_owner() != (attackable)[j]->get_owner()
				&& player->get_owned_territories()[i]->get_num_units() > attackable[j]->get_num_units()){
				std::cout << "\n" << player->get_owned_territories()[i]->get_name() << " attacks "
					<< attackable[j]->get_name() << " (Player " << attackable[j]->get_owner()->get_id()
					<< ")!" << std::endl;
				Battle::SingleBattle(player->get_owned_territories()[i], (attackable)[j]);
			}
		}
	}
}