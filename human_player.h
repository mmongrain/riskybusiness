#ifndef HUMAN_PLAYER_H_
#define HUMAN_PLAYER_H_

class Player;

class HumanPlayer : public Player {

public:
	HumanPlayer() {}
	~HumanPlayer() {}

protected:
	void Reinforce();
	void Attack();
	void Fortify();
};



#endif
