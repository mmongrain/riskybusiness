#include <vector>
#include <iostream>
#include <chrono>
#include <thread>

#include "battle.h"
#include "random_ai_player.h"
#include "territory.h"
#include "ui.h"
#include "player.h"


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