#ifndef aggressive_ai_player_h
#define aggressive_ai_player_h
#include "strategy.h"

class Player;

class Aggressive : public Strategy {
	void Reinforce(Player *player, int reinforcements);
	void Attack(Player *player);
	void Fortify(Player *player);
};

#endif
