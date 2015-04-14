#ifndef strategy_random_h
#define strategy_random_h

#include "strategy.h"

class Player;

class Random : public Strategy {

	public: 
		
		virtual void Fortify(Player *player);
		virtual void Attack(Player *player);
		virtual void Reinforce(Player *player, int reinforcements);


};

#endif
