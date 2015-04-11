#ifndef COMP_PLAYER_H_
#define COMP_PLAYER_H_

#include "player.h"
#include "strategy.h"
#include "territory.h"

class CompPlayer : public Player {
public:
	CompPlayer();	
	void set_strategy(Strategy *strat) {strategy = strat;}
	~CompPlayer(){ delete strategy; strategy = 0; }
	bool WantsToAutoAttack();
	int NumConqueringArmiesToMove(int min, int max);
	std::string type();

protected:
	void Attack();
	void Reinforce();
	void Fortify();

private:
	Strategy *strategy;
	bool WillFortify();
	Territory* ChoosePointOfDepart();
	Territory* ChooseDestination(Territory* move_from);
};

#endif
