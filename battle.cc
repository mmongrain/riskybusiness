#include <iostream>
#include <stdlib.h> // rand()
#include <algorithm> // sort()
#include <functional> // greater()
#include <vector>
#include <time.h> // time()

#include "battle.h"
#include "game.h"
#include "map.h"
#include "human_player.h" 

void battle::Battle(Territory* attacking, Territory* defending) {
	int result = AttackHandler(attacking, defending);
	if (result == 1) {
		Capture(attacking, defending);
		if (Game::Instance().get_game_over() == true)
			return;
	}
	else {
		Retreat(attacking, result);
	}
}

// for HumanPlayer: will ask if he wants to AutoAttack or to attack only once,
// and then will keep doing SingleAttacks until someone wins or until the Player retreats 
// or until he chooses to AutoAttack (automatically attack until it is no longer possible)
// 
// A CompPlayer will always choose to AutoAttack

int battle::AttackHandler(Territory *attacking, Territory *defending) {
	bool auto_attack;

	while (true) {
		auto_attack = attacking->get_owner()->WantsToAutoAttack(); // check if the Player wants to AutoAttack
		if (auto_attack) {
			return AutoAttack(attacking, defending);
		}
		else { // If the player doesn't AutoAttack, perform a SingleAttack and determine if he will attack again
			SingleAttack(attacking, defending);

			if (defending->get_num_units() <= 0)
				return 1; // attacking territory wins			
			else if (attacking->get_num_units() <= 1)
				return 2; // attacking territory loses	
			else {
				if (!(dynamic_cast<HumanPlayer*>(attacking->get_owner()))->WantsToAttack())
					return 3; // player chose to retreat			
			}
		}
	}
}

int battle::AutoAttack(Territory *attacking, Territory *defending){
	while (attacking->get_num_units() > 1 && defending->get_num_units() > 0){
		SingleAttack(attacking, defending);
	}
	if (defending->get_num_units() <= 0)
		return 1; // attacking territory wins
	else
		return 2; // attacking territory loses
}

void battle::SingleAttack(Territory *attacking, Territory *defending){
	int num_atk_dice = DetermineAtkDice(attacking);
	int num_def_dice = DetermineDefDice(defending);
	std::cout << "Player " << attacking->get_owner()->get_id() << " rolls: ";
	std::vector<int> atk_dice = Dice(num_atk_dice);
	std::cout << "Player " << defending->get_owner()->get_id() << " rolls: ";
	std::vector<int> def_dice = Dice(num_def_dice);

	for (unsigned int i = 0; i < def_dice.size() && i < atk_dice.size(); i++) {
		if (atk_dice[i] > def_dice[i] && defending->get_num_units() != 0)
			DecrementUnits(defending);
		else
			DecrementUnits(attacking);
	}
}

void battle::Capture(Territory* attacking, Territory* defending){
	std::cout << attacking->get_name() << " (Player " << attacking->get_owner()->get_id() << ") has prevailed!" << std::endl;
	if (attacking->get_num_units() < 2) {
		std::cout << "The winner did not have enough armies left to capture the conquered territory, "
			<< "so " << defending->get_name() << " is left empty!" << std::endl;
		defending->get_owner()->remove_territory(defending); 
		defending->set_owner(NULL);
	} else {
		int min = DetermineAtkDice(attacking);
		int max = attacking->get_num_units() - 1;
		attacking->get_owner()->CaptureTerritory(attacking, defending, min, max);
	}
}

void battle::Retreat(Territory* attacking, int result){
	if (result == 2)
		std::cout << "The attacking army, humbled, retreats!" << std::endl;
	else
		std::cout << "The attacking army chose to retreat" << std::endl;
}

int battle::DetermineAtkDice(Territory* attacking){
	if (attacking->get_num_units() < 3)
		return attacking->get_num_units() - 1;
	else return 3;
}

int battle::DetermineDefDice(Territory* defending){
	if (defending->get_num_units() < 2)
		return 1;
	else return 2;
}

// move this baby to Territory, it belongs there
void battle::DecrementUnits(Territory* territory){
	territory->set_num_units(territory->get_num_units() - 1);
	std::cout << "Player " << territory->get_owner()->get_id()
		<< " loses a unit!" << std::endl;
}

// Rolls between one and three dice--no more, no less.
// Returns and displays a vector of up to three ints or -1 if input is invalid
std::vector<int> battle::Dice(int num_dice) {
	std::vector<int> out;
	if (num_dice < 1 || num_dice > 3) {
		out.push_back(-1);
		return out;
	}
	else {
		for (int i = 0; i < num_dice; i++)
		{
			// Generates a random int between 1 and 6.
			out.push_back(std::rand() % 6 + 1);
		}
		// Sorts the vector, from begin() to end(), using the > operator
		std::sort(out.begin(), out.end(), std::greater<int>());
		// Displays the vector 
		std::cout << "(";
		unsigned int i = 0;
		for (; i < out.size() - 1; ++i){
			std::cout << out[i] << ", ";
		}
		std::cout << out[i] << ")" << std::endl;
		return out;
	}
}
