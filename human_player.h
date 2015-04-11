#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "player.h"
#include "territory.h"

class HumanPlayer : public Player {

public:
	HumanPlayer() {}
	~HumanPlayer() {}
	bool WantsToAutoAttack();
	bool WantsToAttack();
	void CaptureTerritory(Territory* attacking, Territory* defending, int min, int max);
	int NumConqueringArmiesToMove(int min, int max);
	std::string type();

protected:
	void Reinforce();
	void Attack();
	void Fortify();

private:
	bool AttackIsValid(Territory *attacking, std::string s);
};



#endif
