#ifndef strategy_aggressive_h
#define strategy_aggressive_h

#include "strategy.h"

class Player;

class Aggressive : public Strategy {

	public:

		virtual void Fortify(Player *player);
		virtual void Attack(Player *player);
		virtual void Reinforce(Player *player, int reinforcements);

};

#endif
