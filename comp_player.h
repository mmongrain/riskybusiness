#ifndef COMP_PLAYER_H_
#define COMP_PLAYER_H_

#include "player.h"
#include"strategy.h"

class CompPlayer : public Player {
public:
	CompPlayer();	
	void set_strategy(Strategy *strat) {strategy = strat;}
	~CompPlayer(){ delete strategy; strategy = 0; }
protected:
	void Attack();
	void Reinforce();
	void Fortify();
private:
	Strategy *strategy;
	bool WillFortify();
	Map::Territory* ChoosePointOfDepart();
	Map::Territory* ChooseDestination(Map::Territory* move_from);
};

#endif
