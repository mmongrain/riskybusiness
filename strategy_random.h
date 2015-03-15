#ifndef strategy_random_h
#define strategy_random_h

#include "map.h"
#include "strategy.h"
#include "territory.h"

class CompPlayer;

class Random : public Strategy {
	void execute(CompPlayer *c_player);

private:
	bool WillAttack();
	Territory* FromWhereToAttack(CompPlayer* c_player);
	Territory* WhomToAttack(CompPlayer* c_player, Territory* attacking);
};

#endif
