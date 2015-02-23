#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	Player(int i);
	~Player();
	virtual void PlayTurn();

private:
	int id;

protected:
	virtual void Reinforce();
	virtual void Attack();
	virtual void Move();
};

#endif
