#include <iostream>
#include "player.h"
#include "human_player.h"
#include "battle.h"

HumanPlayer::HumanPlayer() {}
HumanPlayer::~HumanPlayer() {}

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
	Player::Reinforce(); // the Reinforce() in the superclass calculates the number of reinforcements
	while (reinforcements > 0){

		// ask for a territory to reinforce
		std::cout << "You have " << reinforcements << " reinforcements."
			<< "\nChoose which country you want to reinforce: " << std::endl;
		Map::Territory *to_reinforce;
		std::string name;
		std::cin >> name;

		to_reinforce = StringToOwnedTerritory(name);

		if (to_reinforce == NULL)
			continue; // if the no such territory is found, we restart the "while" loop

		// ask for number of armies to put in the chosen territory
		std::cout << "How many armies do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
		int armies;

		// check if number of armies is valid
		while (!(std::cin >> armies) || (armies < 1 && armies > reinforcements))
		{
			if (armies > reinforcements){
				std::cout << "You don't have that many armies!" << std::endl;
			}
			else if (armies < 1){
				std::cout << "You have to place at least 1 army!" << std::endl;
			}
			else {
				std::cout << "Wrong input!" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "So how many armies do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
		}

		// execute the reinforcement 
		reinforcements -= armies;
		to_reinforce->set_units(to_reinforce->get_units() + armies);
		std::cout << armies << " armies have been added to " << to_reinforce->get_name() << std::endl;
	}
}

void HumanPlayer::Attack() {
	int answer;
	std::cout << "\nAttack phase:\nPress 1 to attack or 0 to skip" << std::endl;

	// verify input
	while (!(std::cin >> answer) || (answer != 0 && answer != 1))
	{
		std::cout << "Wrong input! Press 1 to attack or 0 to skip" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	if (answer == 1){
		Map::Territory *attacking = 0;
		Map::Territory *defending = 0;
		std::string name;

		while (attacking == NULL){
			std::cout << "Which territory are you attacking from?" << std::endl;
			std::cin >> name;
			attacking = StringToOwnedTerritory(name);

			if (attacking != NULL){
				if (attacking->get_units < 2){
					std::cout << "You don't have enough units in " << attacking->get_name << "to attack!" << std::endl;
					attacking = NULL;
				}
			}
		}
		while (defending == NULL){
			std::cout << "Which territory do you want to attack?" << std::endl;
			std::cin >> name;
			bool valid = AttackIsValid(attacking, name);
		}
		battle::AllInAttack(attacking, defending);
	}
	else std::cout << "Player " << id << " chose not to attack" << std::endl;
}

void HumanPlayer::Move()
{
	std::cout << "\nFortification phase:\npress 1 to fortify or 0 to skip" << std::endl;
	int answer;

	// verify input
	while (!(std::cin >> answer) || (answer != 0 && answer != 1))
	{
		std::cout << "Wrong input! Press 1 to fortify or 0 to skip" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	if (answer == 1){
		Map::Territory *move_from = 0;
		Map::Territory *move_to = 0;
		int armies = 0;
		std::string name;

		// From which territory to move armies
		while (move_from == NULL){
			std::cout << "From which of your territories do you want to send troops?" << std::endl;
			std::cin >> name;
			move_from = StringToOwnedTerritory(name);
		}

		// To which territory
		while (move_to == NULL || move_from == move_to){ // TODO: also check if they are adjacent 
			std::cout << "To which territory do you want to move troops from " << move_from->get_name() << "?" << std::endl;
			std::cin >> name;
			move_from = StringToOwnedTerritory(name);
		}

		// How many armies to move
		while (!(std::cin >> armies) || (armies < 1 || armies > move_from->get_units() - 1)){
			std::cout << "How many armies do you want to move from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;
			if (armies < 1)
				std::cout << "You have to move at least 1 army!" << std::endl;
			else if (armies > move_from->get_units() - 1)
				std::cout << "You must leave at least 1 army behind!" << std::endl;
			else
				std::cout << "Wrong input!" << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}

		// Execute the movement
		move_from->set_units(get_units() - armies);
		move_to->set_units(get_units() + armies);
		std::cout << armies << " armies successfully moved from " << move_from->get_name() << " to " << move_to->get_name() << std::endl;

	}
	else std::cout << "Player " << id << " chose not to fortify" << std::endl;
}

// converts a string to one of the Territory objects owned by Player
// or outputs an error message and returns a null pointer
Map::Territory* HumanPlayer::StringToOwnedTerritory(std::string s){
	Map::Territory *terr = 0;
	for (unsigned int i = 0; i < owned_territories.size(); i++){
		if (owned_territories[i]->get_name() == s){
			terr = owned_territories[i];
			break;
		}
		else {
			std::cout << "You don't own this territory!" << std::endl;
		}
	}
	return terr;
}

bool HumanPlayer::AttackIsValid(Map::Territory *attacking, std::string s){
	Map::Territory *defending = 0;

	for (unsigned int i = 0; i < Map::get_continents().size(); i++){
		if (Map::get_continent[i]->get_name() == s){
			defending = get_continent[i];
			break;
		}
		else {
			std::cout << "There is no such territory!" << std::endl;
			return false;
		}
		if (defending->get_owner == this){
			std::cout << "You can't attack your own people!";
			return false;
		}
		else if (defending->get_units() < 1) {
			std::cout << "This country is empty!";
			return false;
		}
		else if (attacking->IsAdjacent(defending)){
			std::cout << "Those two countries are not adjacent!";
			return false;
		}
		else
			return true;
	}

}
