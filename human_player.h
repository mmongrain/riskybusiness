#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

#include "player.h"
#include "territory.h"

class HumanPlayer : public Player {

public:
	HumanPlayer() {}
  ~HumanPlayer() {}

protected:
	void Reinforce();
	void Attack();
	void Fortify();

private:
	bool AttackIsValid(Territory *attacking, std::string s);
};



#endif
