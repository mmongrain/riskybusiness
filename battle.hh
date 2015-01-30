#ifndef BATTLE_H
#define BATTLE_H

#include <string>
#include <vector>
#include "battlefixtures.hh"

namespace battle {

	bool attack_is_valid(Country* attacking, Country* defending, int num_atk_dice, int num_def_dice, std::string out);
  std::vector<int> dice(int num_dice);
	int attack(Country* attacking, Country* defending, std::vector<int> atk_dice, std::vector<int> def_dice);
	int all_in_attack(Country* attacking, Country* defending);
	int victory(Country* attacking, Country* defending, int atk_dice);
}

#endif
