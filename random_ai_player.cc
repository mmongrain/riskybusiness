#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "random_ai_player.h"
#include "territory.h"
#include "game.h"
#include "ui.h"

class Player;

void Random::Attack(Player *player){

	// decide between attacking or not
	if (!WillAttack()) {
		std::cout << "CompPlayer " << player->get_id() << " chose not to attack" << std::endl;
		return;
	}

	// choose attacker and defender territories
	Territory* attacking = FromWhereToAttack(player);
	if (attacking == NULL)
		return;
	Territory* defending = WhomToAttack(player, attacking);

	// proceed to attack
	std::cout << "\n" << attacking->get_name() << " attacks " << defending->get_name()
		<< " (Player " << defending->get_owner()->get_id()
		<< ")!" << std::endl;
	Battle::SingleBattle(attacking, defending);

}

void Random::Reinforce(Player *player, int reinforcements){
	if (Game::Instance().slow_mode) { std::this_thread::sleep_for(std::chrono::milliseconds(250)); }	
	// pick a territory
	std::vector<Territory*> owned_territories = player->get_owned_territories();
	Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size()];

	// put all reinforcements there
	to_reinforce->set_num_units(to_reinforce->get_num_units() + reinforcements);
	UI::PrintNumReinforcements(reinforcements, to_reinforce);
}

void Random::Fortify(Player *player) {
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