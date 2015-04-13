#ifndef strategy_random_h
#define strategy_random_h

#include "map.h"
#include "strategy.h"
#include "territory.h"

class Player;

class Random : public Strategy {
	void Reinforce(Player *player, int reinforcements);
	void Attack(Player *player);
	void Fortify(Player *player);

private:

	// maybe move these somewhere else
	bool WillAttack();
	Territory* FromWhereToAttack(Player* player);
	Territory* WhomToAttack(Player* player, Territory* attacking);
	bool WantsToAutoAttack(); 
	int NumConqueringArmiesToMove(int min, int max);
	bool WillFortify();
	Territory* ChoosePointOfDepart(Player *player);
	Territory* ChooseDestination(Player *player, Territory* move_from);
};

#endif
