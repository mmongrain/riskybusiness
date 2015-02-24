#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include <vector>


class Player
{
public:
	Player(int i);
	virtual ~Player();
	virtual void PlayTurn();
	std::vector<Map::Territory *> owned_territories;
	

protected:
	int id;
	virtual void Reinforce() = 0;
	virtual void Attack() = 0;
	virtual void Move() = 0;
};

#endif
