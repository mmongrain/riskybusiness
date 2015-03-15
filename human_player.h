#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "player.h"

class HumanPlayer : public Player {

public:
	HumanPlayer() {}
	~HumanPlayer() {}
	bool WantsToAutoAttack();
	bool WantsToAttack();
	void CaptureTerritory(Map::Territory* attacking, Map::Territory* defending, int min, int max);
	int NumConqueringArmiesToMove(int min, int max);

protected:
	void Reinforce();
	void Attack();
	void Fortify();

private:
	bool AttackIsValid(Map::Territory *attacking, std::string s);
};



#endif
