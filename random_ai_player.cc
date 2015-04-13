
#include <vector>
#include <iostream>
#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "random_ai_player.h"
#include "territory.h"

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