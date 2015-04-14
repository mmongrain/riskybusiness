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

void Aggressive::Reinforce(Player *player, int reinforcements){
	if (Game::Instance().slow_mode) { std::this_thread::sleep_for(std::chrono::milliseconds(250)); }	
	// pick a territory
	std::vector<Territory*> owned_territories = player->get_owned_territories();
	Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size()];

	// put all reinforcements there
	to_reinforce->set_num_units(to_reinforce->get_num_units() + reinforcements);
	UI::PrintNumReinforcements(reinforcements, to_reinforce);
}

void Aggressive::Fortify(Player *player) {
	if (Game::Instance().slow_mode) { std::this_thread::sleep_for(std::chrono::milliseconds(250)); }	
	// decide between fortifying or not
	if (!WillFortify()) {
		UI::StatusMessage("AI Player " + std::to_string(player->get_id()) + " chose not to fortify!");
		return;
	}

	// pick from where
	Territory *move_from = ChoosePointOfDepart(player);
	if (move_from == NULL)
		return;

	// pick to where
	Territory *move_to = ChooseDestination(player, move_from);
	if (move_to == NULL)
		return;

	// move everything there
	int armies = std::rand() % (move_from->get_num_units() - 1) + 1;
	move_from->set_num_units(move_from->get_num_units() - armies);
	move_to->set_num_units(move_to->get_num_units() + armies);
	UI::FortificationComplete(armies, move_from, move_to);
}