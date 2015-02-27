#ifndef COMP_PLAYER_H_
#define COMP_PLAYER_H_

#include "player.h"

class CompPlayer;
class Strategy {
public:
	virtual void execute(CompPlayer *c_player) = 0;
	virtual ~Strategy(){};
};

class Aggressive : public Strategy {
	void execute(CompPlayer *c_player);
};

class CompPlayer : public Player {
public:
	CompPlayer();	
	void set_strategy(Strategy *strat) {strategy = strat;}
	~CompPlayer(){ delete strategy; strategy = 0; }
protected:
	void Attack();
private:
	Strategy *strategy;
};



#endif