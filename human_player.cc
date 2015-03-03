#include <iostream>
#include "player.h"
#include "human_player.h"
#include "battle.h"

// Asks the user to input the name of a territory and a number of 
// reinforcements, does the necessary checks and performs the reinforcement

void HumanPlayer::Reinforce() {
	Player::Reinforce(); // the Reinforce() in the superclass calculates the number of reinforcements
	while (reinforcements > 0){

		// ask for a territory to reinforce
		std::cout << "You have " << reinforcements << " reinforcements."
			<< "\nChoose which territory you want to reinforce: " << std::endl;
		PrintOwnedTerritories();
		Map::Territory *to_reinforce;

		std::string name;
		std::cin.clear();
		std::cin.ignore(1, '\n');
		getline(std::cin, name);
		to_reinforce = StringToOwnedTerritory(name);
		if (to_reinforce == NULL){
			std::cin.clear();
			std::cin.ignore(1000, '\n');
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
				std::cout << "You have to place at least 1 reinforcement!" << std::endl;
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

	while (answer == 1) {
		Map::Territory *attacking = 0;
		Map::Territory *defending = 0;
		std::string name;

    // Read in & verify attacking country
		for (;;) {
			std::cout << "Which territory are you attacking from?" << std::endl;
      PrintOwnedTerritories();
      // Use getline instead of std::cin so it doesn't break on spaces
      std::cin.ignore(1, '\n');
      std::cin.clear();
			getline(std::cin, name);
			attacking = Map::Instance().StringToTerritory(name);

      bool flag = false;
			if (attacking) {
				if (attacking->get_num_units() < 2) {
					std::cout << "You don't have enough units in " << attacking->get_name() << " to attack!" << std::endl;
		    } else if (attacking->get_owner() != this) {
          std::cout << "That's not yours to attack with!" << std::endl;
        } else { flag = true; }
			}
      if (flag) break;
		}

		for (;;) {
			std::cout << "Which territory do you want to attack?" << std::endl;
      attacking->PrintAttackableTerritories(this);
      std::cin.clear();
			getline(std::cin, name);
      if (Map::Instance().StringToTerritory(name)) {
        defending = Map::Instance().StringToTerritory(name);
        break;
      }
      std::cout << "Nope!!" << std::endl;
		}
		battle::Battle(attacking, defending);
    std::cout << "Do you wish to attack another country? Enter 1 for yes, or 0 for no." << std::endl;
    std::cin.clear();
    std::cin >> answer;
	}
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
	for (;;) {
      for (;;) {
        std::cout << "From which of your territories do you want to send troops?" << std::endl;
        PrintOwnedTerritories();
        std::cin.ignore(1, '\n');
        std::cin.clear();
        getline(std::cin, name);
        if (Map::Instance().StringToTerritory(name)) {
          move_from = Map::Instance().StringToTerritory(name);
          if (move_from->get_owner() == this) break;
          std::cout << "That country doesn't belong to you!" << std::endl;
        }
      }

      // To which territory
      for (;;) {
        std::cout << "To which of your territories do you want to send troops?" << std::endl;
        move_from->PrintAdjacentOwnedTerritories(this);
        // XXX: This ignore and the next break the entry on my system, idk why rn
        // If it works fine on yours please delete this comment and the line
        // If not please wrap in a linux #ifdef, thanks!!   --Matthew
        // std::cin.ignore(1, '\n');
        std::cin.clear();
        getline(std::cin, name);
        if (Map::Instance().StringToTerritory(name)) {
          move_to = Map::Instance().StringToTerritory(name);
          if (move_to->get_owner() == this) break;
          std::cout << "That country doesn't belong to you!" << std::endl;
        }
      }
    if (move_from->AreAdjacent(move_to)) break;
    std::cout << "Those countries aren't adjacent!" << std::endl;
    }
		
		// How many armies to move
		for (;;) {
			std::cout << "How many armies do you want to move from " 
                << move_from->get_name() << " to " << move_to->get_name() << "?\n";
			std::cin.clear();
			// std::cin.ignore(1, '\n');
     		std::cin >> armies;
      
			if (armies < 1) {
				std::cout << "You have to move at least 1 army!" << std::endl;
			} else if (armies > move_from->get_num_units() - 1) {
				std::cout << "You must leave at least 1 army behind!" << std::endl;
			} else break;
		}

		// Execute the movement
		move_from->set_num_units(move_from->get_num_units() - armies);
		move_to->set_num_units(move_to->get_num_units() + armies);
		std::cout << armies << " armies successfully moved from " 
              << move_from->get_name() << " to " << move_to->get_name() << "!\n";

	}
	else std::cout << "Player " << id << " chose not to fortify" << std::endl;
}

