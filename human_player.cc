#include <iostream>

#include "battle.h"
#include "human_player.h"
#include "player.h"
#include "territory.h"

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
	CalculateReinforcements(); // calculates the number of reinforcements
	while (reinforcements > 0){

		// ask for a territory to reinforce
		std::cout << "You have " << reinforcements << " reinforcements."
			<< "\nWhich territory would you like to reinforce? " << std::endl;
		PrintOwnedTerritories();
		Territory *to_reinforce;
		std::string name;
		getline(std::cin, name);
		to_reinforce = StringToOwnedTerritory(name);
		if (to_reinforce == NULL) {
			std::cout << "Territory not found!" << std::endl;
			continue; // if the no such territory is found, we restart the "while" loop
		}
		// ask for number of armies to put in the chosen territory
		std::cout << "How many armies do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
		int armies;

		// check if number of armies is valid
		while (!(std::cin >> armies) || (armies < 1 && armies > reinforcements))
		{
			if (armies > reinforcements){
				std::cout << "You don't have that many reinforcements!" << std::endl;
			}
			else if (armies < 1){
				std::cout << "You have to place at least one reinforcement!" << std::endl;
			}
			else {
				std::cout << "Wrong input!" << std::endl;
			}
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "How many reinforcements do you want to place in " << to_reinforce->get_name() << "?" << std::endl;
		}

		// execute the reinforcement 
		reinforcements -= armies;
		to_reinforce->set_num_units(to_reinforce->get_num_units() + armies);
		std::cout << armies << " armies have been added to "
			<< to_reinforce->get_name() << "." << std::endl;
	}
}

void HumanPlayer::Attack() {
	bool skip_flag = false;
	int answer;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::cout << "\nAttack phase:\nPress 1 to attack or 0 to skip." << std::endl;
	std::cin >> answer;
	// verify input
	while (answer != 0 && answer != 1) {
		std::cout << "Wrong input! Press 1 to attack or 0 to skip." << std::endl;
		std::cin >> answer;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
	}

	while (answer == 1) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		Territory *attacking = 0;
		Territory *defending = 0;
		std::string name;

		// Read in & verify attacking country
		for (;;) {
			std::cout << "Which territory are you attacking from? (Enter q to skip.)" << std::endl;
			PrintOwnedTerritories();
			// Use getline instead of std::cin so it doesn't break on spaces
			getline(std::cin, name);
			if (name.compare("q") == 0) {
				skip_flag = true;
				break;
			}

			attacking = Map::Instance().StringToTerritory(name);

			if (attacking) {
				if (attacking->get_num_units() < 2) {
					std::cout << "You don't have enough units in " << attacking->get_name() << " to attack!" << std::endl;
				}
				else if (attacking->get_owner() != this) {
					std::cout << "That's not yours to attack with!" << std::endl;
				}
				else if (!(attacking->CanAttack())) {
					std::cout << "No countries attackable from that country!\n";
				}
				else break;
			}
		}

		if (skip_flag) { break; }

		for (;;) {
			std::cout << "Which territory do you want to attack? (Enter q to skip.)" << std::endl;
			attacking->PrintAttackableTerritories(this);
			getline(std::cin, name);
			if (name.compare("q") == 0) { break; }
			if (Map::Instance().StringToTerritory(name)) {
				defending = Map::Instance().StringToTerritory(name);
				break;
			}
			std::cout << "Nope!!" << std::endl;
		}
		if (defending) { battle::Battle(attacking, defending); }
		std::cout << "Do you wish to attack another country? Enter 1 for yes, or 0 for no." << std::endl;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cin >> answer;
	}
}

void HumanPlayer::Fortify() {

	Territory *move_from = 0;
	Territory *move_to = 0;
	int armies = 0;
	std::string name;
	bool skip_flag = false;

	std::cout << "\nFortification phase:\nPress 1 to fortify or 0 to skip" << std::endl;
	int answer;
	std::cin >> answer;

	// verify input
	while ((answer != 0 && answer != 1)) {
		std::cout << "Wrong input! Press 1 to fortify or 0 to skip" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cin >> answer;
	}
	std::cin.clear();
	std::cin.ignore(10000, '\n');

	if (answer == 1) {

		// From which territory to move armies
		for (;;) {
			std::cout << "From which of your territories do you want to send troops? (Enter q to skip.)" << std::endl;
			PrintOwnedTerritories();
			getline(std::cin, name);
			if (name.compare("q") == 0) {
				skip_flag = true;
				break;
			}
			if (Map::Instance().StringToTerritory(name)) {
				move_from = Map::Instance().StringToTerritory(name);
				if (move_from->get_owner() != this) {
					std::cout << "That territory doesn't belong to you!" << std::endl;
				}
				else if (!(move_from->CanFortify())) {
					std::cout << "Can't fortify any other territories from that one!" << std::endl;
				}
				else break;
			}
		}

		if (!skip_flag) {

			// To which territory
			for (;;) {
				std::cout << "To which of your territories do you want to send troops? (Enter q to skip.)" << std::endl;
				move_from->PrintAdjacentOwnedTerritories(this);
				getline(std::cin, name);
				if (name.compare("q") == 0) {
					skip_flag = true;
					break;
				}
				if (Map::Instance().StringToTerritory(name)) {
					move_to = Map::Instance().StringToTerritory(name);
					if (move_to->get_owner() != this) {
						std::cout << "That country doesn't belong to you!" << std::endl;
					}
					else if (!(move_from->AreAdjacent(move_to))) {
						std::cout << "Those countries aren't adjacent!" << std::endl;
					}
					else break;
				}
			}
		}

		if (!skip_flag) {

			for (;;) {
				std::cout << "How many armies do you want to move from "
					<< move_from->get_name() << " to " << move_to->get_name() << "?\n";
				std::cin >> armies;

				if (armies < 1) {
					std::cout << "You have to move at least 1 army!" << std::endl;
				}
				else if (armies > move_from->get_num_units() - 1) {
					std::cout << "You must leave at least 1 army behind!" << std::endl;
				}
				else break;
			}
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			// Execute the movement
			move_from->set_num_units(move_from->get_num_units() - armies);
			move_to->set_num_units(move_to->get_num_units() + armies);
			std::cout << armies << " armies successfully moved from "
				<< move_from->get_name() << " to " << move_to->get_name() << "!\n";
		}
	}
	if (answer == 0 || skip_flag) {
		std::cout << "Player " << id << " chose not to fortify" << std::endl;
	}
}

// used for battles
bool HumanPlayer::WantsToAutoAttack(){
	std::string answer;
	std::cout << "Do you want to auto-attack? (y/n)" << std::endl;
	std::cin >> answer;
	while (answer != "y" && answer != "n"){
		std::cout << "Wrong input! Do you want to auto-attack? (y/n)" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	if (answer == "y")
		return true;
	else return false;
}

bool HumanPlayer::WantsToAttack(){
	char answer;
	std::cout << "Continue attacking? (y/n)" << std::endl;
	std::cin >> answer;
	while (answer != 'y' && answer != 'n'){
		std::cout << "Wrong input! Continue attacking? (y/n)" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	if (answer == 'y')
		return true;
	else return false;
}

int HumanPlayer::NumConqueringArmiesToMove(int min, int max){
	int answer;
	std::cout << "How many armies do you want to install in the conquered territory (" << min << "-" << max << ")?" << std::endl;
	std::cin >> answer;
	while (answer < min || answer > max){
		std::cout << "Wrong input! How many armies do you want to install in the conquered territory (" << min << "-" << max << ")?" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	return answer;
}

