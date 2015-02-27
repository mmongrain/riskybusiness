#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "player.h"

class HumanPlayer : public Player {

public:
	HumanPlayer();
  ~HumanPlayer();

protected:
	void Reinforce();
	void Attack();
	void Move();

private:
	Map::Territory* StringToOwnedTerritory(std::string s);
	bool AttackIsValid(Map::Territory *attacking, std::string s);
};



#endif
