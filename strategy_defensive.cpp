#include "strategy_defensive.h"
#include <vector>
#include "map.h"
#include "battle.h"
#include "comp_player.h"

class CompPlayer;

void Defensive::execute(CompPlayer *c_player){
	unsigned int j;
	bool hasAttacked;
	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){

		std::vector<Map::Territory*> attackable = c_player->owned_territories[i]->GetAttackableTerritories(c_player);
		
		// iterates through attackable territories and checks if all of them have 
		// at least 4 armies less than its own territory, if yes, then attacks the first one
		for (j = 0; j < attackable.size(); j++){

			if (c_player->owned_territories[i]->get_owner() != (attackable)[j]->get_owner()
				&& c_player->owned_territories[i]->get_num_units() < attackable[j]->get_num_units() + 4){
				break; // at least one adjacent enemy country that doesn't 
						// meet its criteria has been found, so it stops
			}
		}
		// if it reaches this point, then it thinks it is safe to attack from owned_territories[i]
		battle::Battle(c_player->owned_territories[i], (attackable)[j]);	
		hasAttacked = true;
	}
	if (!hasAttacked){
		std::cout << "CompPlayer " << c_player->get_id() << " chose not to attack" << std::endl;
	}
}