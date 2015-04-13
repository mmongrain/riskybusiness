#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "strategy.h"

class Player;

class HumanPlayer : public Strategy {
	virtual void Reinforce(Player *player, int reinforcements);
	virtual void Attack(Player *player);
	virtual void Fortify(Player *player);
	virtual int GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending);
	virtual bool AutoAttackChoice();
};


#endif
