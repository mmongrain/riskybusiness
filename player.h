#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player(int i);
	~Player();
	void PlayTurn();

private:
	int id;
	void Reinforce();
	void Attack();
	void Move();
};

#endif
