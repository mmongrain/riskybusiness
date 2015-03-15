#include <vector>

#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "strategy_aggressive.h"
#include "territory.h"

class CompPlayer;

// attacks the first neighbor enemy territory which has less 
// armies than one of its own territories acjacent to it

void Aggressive::execute(CompPlayer *c_player){

	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){

		std::vector<Territory*> attackable = c_player->owned_territories[i]->GetAttackableTerritories(c_player);

		// iterates through adjacent territories and attacks the first valid target
		for (unsigned int j = 0; j < attackable.size(); j++){

			if (c_player->owned_territories[i]->get_owner() != (attackable)[j]->get_owner()
				&& c_player->owned_territories[i]->get_num_units() > attackable[j]->get_num_units()){
				std::cout << "\n" << c_player->owned_territories[i]->get_name() << " attacks "
					<< attackable[j]->get_name() << " (Player " << attackable[j]->get_owner()->get_id()
					<< ")!" << std::endl;
				battle::Battle(c_player->owned_territories[i], (attackable)[j]);
			}
		}
	}
}
