#include <vector>
#include <iostream>
#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "strategy_random.h"
#include "territory.h"

class CompPlayer;

void Random::execute(CompPlayer *c_player){

	// decide between attacking or not
	if (!WillAttack()) {
		std::cout << "CompPlayer " << c_player->get_id() << " chose not to attack" << std::endl;
		return;
	}

	// choose attacker and defender territories
	Territory* attacking = FromWhereToAttack(c_player);
	if (attacking == NULL)
		return;
	Territory* defending = WhomToAttack(c_player, attacking);

	// proceed to attack
	std::cout << "\n" << attacking->get_name() << " attacks " << defending->get_name()
		<< " (Player " << defending->get_owner()->get_id()
		<< ")!" << std::endl;
	Battle::SingleBattle(attacking, defending);

}

// randomly chooses between attacking or not
bool Random::WillAttack(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid attacking territory or null if no such territory is found
Territory* Random::FromWhereToAttack(CompPlayer* c_player){
	std::vector <Territory*> valid_attackers;
	std::vector <Territory*> owned_territories = c_player->get_owned_territories();

	// gathers all valid_attackers 
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanAttack())
			valid_attackers.push_back(owned_territories[i]);
	}

	// doesn't attack if there is no valid attackers
	if (valid_attackers.size() == 0){
		std::cout << "CompPlayer " << c_player->get_id() << "could not attack" << std::endl;
		return NULL;
	}

	// randomly chooses and returns one of the valid_attackers
	Territory* attacking = valid_attackers[std::rand() % valid_attackers.size()];
	return attacking;
}

// randomly chooses and returns a valid target territory to be attacked
Territory* Random::WhomToAttack(CompPlayer* c_player, Territory* attacking){
	std::vector <Territory*> attackable = attacking->GetAttackableTerritories(c_player);
	Territory* defending = attackable[std::rand() % attackable.size()];
	return defending;
}
