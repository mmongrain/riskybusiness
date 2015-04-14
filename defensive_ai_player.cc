#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "defensive_ai_player.h"
#include "territory.h"
#include "game.h"
#include "ui.h"

class CompPlayer;

void Defensive::Attack(Player *player){
	unsigned int j;
	bool has_attacked = false;
	bool ok_to_attack;
	// iterates through its own terrirories
	for (unsigned int i = 0; i < player->get_owned_territories().size(); i++){
		ok_to_attack = true;
		if (!player->get_owned_territories()[i]->CanAttack() || player->get_owned_territories()[i] == NULL)
			continue;
		std::vector<Territory*> attackable = player->get_owned_territories()[i]->GetAttackableTerritories(player);

		// iterates through attackable territories and checks if all of them have 
		// at least 4 armies less than its own territory, if yes, then attacks the first one
		for (j = 0; j < attackable.size() - 1; j++){
			if (player->get_owned_territories()[i]->get_num_units() < (attackable[j]->get_num_units() + 4)){
				ok_to_attack = false; // at least one adjacent enemy country that doesn't 
				// meet its criteria has been found, so it won't attack
			}
		}
		if (ok_to_attack){
			std::cout << "\n" << player->get_owned_territories()[i]->get_name() << " attacks "
				<< attackable[0]->get_name() << " (Player " << attackable[0]->get_owner()->get_id()
				<< ")!" << std::endl;
			Battle::SingleBattle(player->get_owned_territories()[i], attackable[0]);
			has_attacked = true;
		}
	}
	if (!has_attacked){
		std::cout << "CompPlayer " << player->get_id() << " chose not to attack" << std::endl;
	}
}