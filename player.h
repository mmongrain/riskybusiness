#pragma once
class Player
{
public:
	Player(int i);
	~Player();
	void playTurn();

private:
	int id;
	void reinforce();
	void attack();
	void move();
};

