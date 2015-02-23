#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>

class Player
{
public:
	Player(int i);
	~Player();
	virtual void PlayTurn();
	std::vector<std::string> owned_territories;
	

private:
	int id;

protected:
	virtual void Reinforce();
	virtual void Attack();
	virtual void Move();
};

#endif
