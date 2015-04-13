#ifndef strategy_defensive_h
#define strategy_defensive_h
#include "strategy.h"

class Player;

class Defensive : public Strategy {
	void Reinforce(Player *player, int reinforcements);
	void Attack(Player *player);
	void Fortify(Player *player);

private:
	bool has_attacked;
};

#endif
