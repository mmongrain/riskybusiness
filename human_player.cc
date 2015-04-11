#include <iostream>
#include <string>
#include "battle.h"
#include "human_player.h"
#include "player.h"
#include "territory.h"
#include "ui.h"


// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
  CalculateReinforcements();
	while (reinforcements > 0){
    Territory* to_reinforce = UI::GetReinforceableTerritory(this);
    int armies = UI::GetNumReinforcements(this, to_reinforce);
		reinforcements -= armies;
		to_reinforce->set_num_units(to_reinforce->get_num_units() + armies);
	}
}

void HumanPlayer::Attack() {
	phase = 2; // for save/load of game in progress
	bool skip_flag = false;
  UI::StartAttackPhase(this);
  while (UI::AttackChoice()) {
    Territory *attacking = UI::GetAttackingTerritory(this);
    if (attacking == NULL) { continue; }
    Territory *defending = UI::GetDefendingTerritory(this, attacking);
    if (defending == NULL) { continue; }
    Battle::SingleBattle(attacking, defending);
	}
			}

void HumanPlayer::Fortify() {
	phase = 3; // for save/load of game in progress
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


int HumanPlayer::NumConqueringArmiesToMove(int min, int max){
	int answer;
  max = (min > max) ? min : max;
	std::cout << "How many armies do you want to install in the conquered territory (" << min << "-" << max << ")?" << std::endl;
	std::cin >> answer;
	while (answer < min || answer > max){
		std::cout << "Wrong input! How many armies do you want to install in the conquered territory (" << min << "-" << max << ")?" << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
    std::cin >> answer;
	}
	return answer;
}

std::string HumanPlayer::type() { return "HumanPlayer"; }