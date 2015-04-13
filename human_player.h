#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "strategy.h"

class Player;

class HumanPlayer : public Strategy {
	void Reinforce(Player *player, int reinforcements);
	void Attack(Player *player);
	void Fortify(Player *player);
};


#endif
