#include <stdio>
#include <stdlib.h> // rand()
using namespace std;

namespace battle 
{
	// Tests whether an attack is valid.
	bool attack_is_valid(Country attacking, Country defending, int atk_dice, int def_dice, string out)
	{
		if (attacking.owner != defending.owner) {
			out = "You can't attack your own people!";
			return false;
		} else if (attacking.units < 1 || defending.units < 1) {
			out = "One of those countries is empty!";
			return false;
		} else if (atk_dice < 1 || atk_dice > 3) {
			out = "Invalid number of attacking dice!";
			return false;
		} else if (def_dice < 1 || def_dice > 2) {
			out = "Invalid number of defending dice!";
		} else if (attacking.owner != current_player) {
			out = "Not that player's turn!";
			return false;
		} else if (attacking.units - num_dice < 1) {
			out = "Attacker does not have enough units!";
			return false;
		} else if (attacking.units < defending units) {
			out = "Cannot be more defenders than attackers!";
			return false;
		} else if (!Country::areAdjacent(attacking, defending)) {
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
			}
			// Bubblesort out[] 
			if (out[0] < out[1] && num_dice > 1) {
				int t = out[0];
				out[0] = out[1];
				out[1] = t;
			}
			if (out[1] < out[2] && num_dice == 3) {
				int t = out[1];
				out[1] = out[2];
				out[2] = t;
			}
			if (out[0] < out[1] && num_dice == 3) {
				int t = out[0];
				out[0] = out[1];
				out[1] = t;
			}
			return out;
		}
	}
	
	// Stages a single attack.
	// Returns -1 and a message to cout on error, 1 if the attacking country wins,
	// and 0 otherwise.
	int attack (Country attacking, Country defending, int atk_dice, int def_dice)
	{
		string message;
		if (!attack_is_valid(attacking, defending, atk_dice, def_dice, message) {
			cout << message << endl;
			return -1;
		}
		int attackers [3] = dice(num_dice);
		int defenders [3] = dice(num_dice);
		for (int i = 0; i < def_dice; i++)
		{
			if (attackers[i] > defenders[i]) {
				defending.units = defending.units - 1;
			} else {
				attacking.units = attacking.units - 1;
			}
			if (defenders.units = 0) {
				victory(attacking, defending, atk_dice, num_units);
				return 1;
			}
		}
		return 0;
	}

	int all_in_attack (Country attacking, Country defending)
	{
		while (attacking.units > 1)
		{
			int dice = 1;
			while (attacking.units - dice > 1 && dice < 4) { 
				++dice;
			}
			attack(dice);
		}
	}
}	
