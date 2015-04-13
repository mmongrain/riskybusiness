#ifndef strategy_random_h
#define strategy_random_h

#include "strategy.h"

class Player;

class Random : public Strategy {

	public: 
		
		void Attack(Player *player);

};

#endif
