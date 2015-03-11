#ifndef strategy_defensive_h
#define strategy_defensive_h
#include "strategy.h"

class CompPlayer;

class Defensive : public Strategy {
	void execute(CompPlayer *c_player);
};

#endif