#ifndef strategy_aggressive_h
#define strategy_aggressive_h
#include "strategy.h"

class CompPlayer;

class Aggressive : public Strategy {
	void execute(CompPlayer *c_player);
};

#endif