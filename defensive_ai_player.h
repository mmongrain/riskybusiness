#ifndef strategy_defensive_h
#define strategy_defensive_h

#include "strategy.h"

class Player;

class Defensive : public Strategy {

	public:
		
		virtual void Fortify(Player *player);
		virtual void Attack(Player *player);
		virtual void Reinforce(Player *player, int reinforcements);

	private:

		bool has_attacked;
};

#endif
