#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include "battlefixtures.h"

namespace battle {

	bool attack_is_valid(Country* attacking, Country* defending, int atk_dice, int def_dice, std::string out);
	int dice(int number, int results[]);
	int attack(Country* attacking, Country* defending, int atk_dice, int def_dice);
	int all_in_attack(Country* attacking, Country* defending);
	int victory(Country* attacking, Country* defending, int atk_dice);
}

#endif
