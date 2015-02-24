#pragma once
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
	virtual void Reinforce();
	virtual void Attack();
	virtual void Move();
};


