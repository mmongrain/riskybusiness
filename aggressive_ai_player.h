#ifndef strategy_aggressive_h
#define strategy_aggressive_h

#include "strategy.h"

class Player;

class Aggressive : public Strategy {

	public:

		virtual void Attack(Player *player);

};

#endif
