#include <iostream>
#include <stdlib.h> // rand()
#include "battle.h"
#include "battlefixtures.h"

namespace battle
{
	// Tests whether an attack is valid.
	bool attack_is_valid(Country* attacking, Country* defending, int atk_dice, int def_dice, std::string out)
	{
		int current_player = 1;
		if (attacking->owner != defending->owner) {
			out = "You can't attack your own people!";
			return false;
		} else if (attacking->units < 1 || defending->units < 1) {
			out = "One of those countries is empty!";
			return false;
		} else if (atk_dice < 1 || atk_dice > 3) {
			out = "Invalid number of attacking dice!";
			return false;
		} else if (def_dice < 1 || def_dice > 2) {
			out = "Invalid number of defending dice!";
			return false;
		} else if (attacking->owner != current_player) {
			out = "Not that player's turn!";
			return false;
		} else if (attacking->units - atk_dice < 1) {
			out = "Attacker does not have enough units!";
			return false;
		} else if (attacking->units < defending->units) {
			out = "Cannot be more defenders than attackers!";
			return false;
		} else if (!Country::are_adjacent(attacking, defending)) {
			out = "Those two countries are not adjacent!";
			return false;
		} else return true;
	}

	// Rolls between one and three dice--no more, no less.
	// Returns a pointer to an array of three ints, each of which represents a
	// die roll, sorted in decreasing numerical order.
	// Deals with invalid input by returning an array of 0's.
	int * dice(int num_dice)
	{
		int out [3];
		if (num_dice < 1 || num_dice > 3) {
			return out;
		} else {
			for (int i = 0; i < num_dice; i++)
			{
				out[i] = rand() % 6 + 1;
				// This bit (bubble)sorts the array as it goes
				// for convenience to the attack() method.
				if (i != 0 && out[i+1] < out[i]) {
					int t = out[i+1];
					out[i] = out[i+1];
					out[i+1] = t;
				}
				if (i == 2 && out[0] > out[1]) {
					int t = out[1];
					out[1] = out[0];
					out[0] = t;
				}
			}
			return out;
		}
	}

	// Stages a single attack.
	// Returns -1 and a message to cout on error, 1 if the attacking country wins,
	// and 0 otherwise.
	int attack (Country* attacking, Country* defending, int atk_dice, int def_dice)
	{
		std::string message;
		if (!attack_is_valid(attacking, defending, atk_dice, def_dice, message)) {
			std::cout << message << std::endl;
			return -1;
		}
		int* attackers = dice(atk_dice); 
		int* defenders = dice(def_dice);
		for (int i = 0; i < def_dice && i < atk_dice; i++)
		{
			if (attackers[i] > defenders[i]) {
				defending->units = defending->units - 1;
			} else {
				attacking->units = attacking->units - 1;
			}
			if (defending->units = 0) {
				return 1;
			}
		}
		return 0;
	}

	// Triggers an all-out attack, using the maximum of dice on both sides
	// until a victor is determined.
	int all_in_attack (Country* attacking, Country* defending)
	{
		while (attacking->units > 1) {
			int num_atk_dice = 1;
			int num_def_dice = 1;
			while (attacking->units - num_atk_dice > 1 && num_atk_dice < 4) {
				++num_atk_dice;
			}
			while (defending->units - num_def_dice > 1 && num_def_dice < 3) {
				++num_def_dice;
			}
			attack(attacking, defending, num_atk_dice, num_def_dice);
		}
	}

	int victory (Country* attacking, Country* defending, int num_units) {
	}
}
