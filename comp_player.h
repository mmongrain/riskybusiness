#ifndef COMP_PLAYER_H_
#define COMP_PLAYER_H_

#include "strategy.h"
#include "player.h"

class CompPlayer : public Player {

public:
	void set_strategy(Strategy *strat){
		strategy = strat;
	}
	Strategy *strategy;

protected:
	void Attack();




};

#endif