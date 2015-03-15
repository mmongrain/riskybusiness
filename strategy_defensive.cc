#include <vector>

#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "strategy_defensive.h"
#include "territory.h"

class CompPlayer;

void Defensive::execute(CompPlayer *c_player){
	unsigned int j;
	bool has_attacked = false;
	bool ok_to_attack;
	// iterates through its own terrirories
	for (unsigned int i = 0; i < c_player->owned_territories.size(); i++){
		ok_to_attack = true;
		if (!c_player->owned_territories[i]->CanAttack() || c_player->owned_territories[i] == NULL)
			continue;
		std::vector<Territory*> attackable = c_player->owned_territories[i]->GetAttackableTerritories(c_player);

		// iterates through attackable territories and checks if all of them have 
		// at least 4 armies less than its own territory, if yes, then attacks the first one
		for (j = 0; j < attackable.size() - 1; j++){
			if (c_player->owned_territories[i]->get_num_units() < (attackable[j]->get_num_units() + 4)){
				ok_to_attack = false; // at least one adjacent enemy country that doesn't 
				// meet its criteria has been found, so it won't attack
			}
		}
		if (ok_to_attack){
			std::cout << "\n" << c_player->owned_territories[i]->get_name() << " attacks "
				<< attackable[0]->get_name() << " (Player " << attackable[0]->get_owner()->get_id()
				<< ")!" << std::endl;
			battle::Battle(c_player->owned_territories[i], attackable[0]);
			has_attacked = true;
		}
	}
	if (!has_attacked){
		std::cout << "CompPlayer " << c_player->get_id() << " chose not to attack" << std::endl;
	}
}
