#ifndef strategy_random_h
#define strategy_random_h
#include "strategy.h"

class CompPlayer;

class Random : public Strategy {
	void execute(CompPlayer *c_player);

private:
	bool WillAttack();
	Map::Territory* FromWhereToAttack(CompPlayer* c_player);
	Map::Territory* WhomToAttack(CompPlayer* c_player, Map::Territory* attacking);
};

#endif