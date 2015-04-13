#include <vector>
#include <iostream>
#include "battle.h"
#include "comp_player.h"
#include "map.h"
#include "random_ai_player.h"
#include "territory.h"

class Player;

void Random::Reinforce(Player *player, int reinforcements){
	// pick a territory
	std::vector<Territory*> owned_territories = player->get_owned_territories();
	Territory *to_reinforce = owned_territories[std::rand() % owned_territories.size()];

	// put all reinforcements there
	to_reinforce->set_num_units(to_reinforce->get_num_units() + reinforcements);
	std::cout << reinforcements << " armies have been added to " << to_reinforce->get_name() << std::endl;
}

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

// randomly chooses between attacking or not
bool Random::WillAttack(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid attacking territory or null if no such territory is found
Territory* Random::FromWhereToAttack(Player* player){
	std::vector <Territory*> valid_attackers;
	std::vector <Territory*> owned_territories = player->get_owned_territories();

	// gathers all valid_attackers 
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanAttack())
			valid_attackers.push_back(owned_territories[i]);
	}

	// doesn't attack if there is no valid attackers
	if (valid_attackers.size() == 0){
		std::cout << "CompPlayer " << player->get_id() << "could not attack" << std::endl;
		return NULL;
	}

	// randomly chooses and returns one of the valid_attackers
	Territory* attacking = valid_attackers[std::rand() % valid_attackers.size()];
	return attacking;
}

// randomly chooses and returns a valid target territory to be attacked
Territory* Random::WhomToAttack(Player* player, Territory* attacking){
	std::vector <Territory*> attackable = attacking->GetAttackableTerritories(player);
	Territory* defending = attackable[std::rand() % attackable.size()];
	return defending;
}

void Random::Fortify(Player *player) {
	std::cout << "\nFortification phase:" << std::endl;
	// decide between fortifying or not
	if (!WillFortify()) {
		std::cout << "CompPlayer " << player->get_id() << " chose not to fortify" << std::endl;
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
	std::cout << armies << " armies successfully moved from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;
}

bool Random::WillFortify(){
	bool will_attack = (std::rand() % 2 == 1) ? true : false;
	return will_attack;
}

// returns a random valid territory from which troops will be moved or null if no such territory is found
Territory* Random::ChoosePointOfDepart(Player *player){
	std::vector <Territory*> valid_points_of_depart;
	std::vector <Territory*> owned_territories = player->get_owned_territories();

	// gathers all valid_points_of_depart
	for (unsigned int i = 0; i < owned_territories.size(); ++i){
		if (owned_territories[i]->CanFortify())
			valid_points_of_depart.push_back(owned_territories[i]);
	}

	// doesn't fortify if there is no valid valid_points_of_depart
	if (valid_points_of_depart.size() == 0){
		std::cout << "CompPlayer " << player->get_id() << " could not fortify" << std::endl;
		return NULL;
	}

	// randomly chooses and returns one of the valid_points_of_depart
	Territory* point_of_depart = valid_points_of_depart[std::rand() % valid_points_of_depart.size()];
	return point_of_depart;
}

Territory* Random::ChooseDestination(Player *player, Territory* move_from){
	std::vector <Territory*> adjacent_owned_territories = move_from->GetAdjacentOwnedTerritories(player);
	if (adjacent_owned_territories.size() == 0){
		std::cout << "CompPlayer " << player->get_id() << " wanted to fortify, but did not"
			<< " find anywhere to move his troops to!" << std::endl;
		return NULL;
	}
	Territory* destination = adjacent_owned_territories[std::rand() % adjacent_owned_territories.size()];
	return destination;
}

bool Random::WantsToAutoAttack(){
	return true;
}

int Random::NumConqueringArmiesToMove(int min, int max){
	return max;
}