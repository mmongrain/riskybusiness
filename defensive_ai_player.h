#ifndef strategy_defensive_h
#define strategy_defensive_h

#include "strategy.h"

class Player;

class Defensive : public Strategy {

	public:
		
		virtual void Attack(Player *player);

};

#endif
