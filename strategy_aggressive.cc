#include "strategy_aggressive.h"
#include <vector>
#include "map.h"
#include "battle.h"
#include "comp_player.h"

class CompPlayer;

void Aggressive::execute(CompPlayer *c_player){

	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){

		std::vector<Map::Territory*> attackable = c_player->owned_territories[i]->GetAttackableTerritories(c_player);

		// iterates through adjacent territories and attacks the first valid target
		for (unsigned int j = 0; j < attackable.size(); j++){

			if (c_player->owned_territories[i]->get_owner() != (attackable)[j]->get_owner()
				&& c_player->owned_territories[i]->get_num_units() > attackable[j]->get_num_units()){

				battle::Battle(c_player->owned_territories[i], (attackable)[j]);
			}
		}
	}
}