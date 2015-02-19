#include "Player.h"
#include <iostream>


Player::Player(int i)
{
	id = i;
}
using namespace std;

void Player::playTurn()
{
	cout << "\n\n=== PLAYER " << id << "'S TURN ==" << endl;
	reinforce();
	attack();
	move();
}

void Player::reinforce()
{
	cout << "\nReinforcement phase:\nPlayer " << id << " reinforced" << endl;
}

void Player::attack()
{
	int answer;
	cout << "\nAttack phase:\nPress 1 to attack or 0 to skip"<< endl;
	
	// verify input
	while (!(cin >> answer) || (answer != 0 && answer != 1)) 
	{	
		cout << "Wrong input! Press 1 to attack or 0 to skip" << endl;
		cin.clear();
		cin.ignore (1000, '\n');
	}

	if (answer == 1)
		cout << "Player " << id << " attacked country X from country Z" << endl;
	else cout << "Player " << id << " chose not to attack" << endl;
}

void Player::move()
{
	cout << "\nFortification phase:\npress 1 to move or 0 to skip" << endl;
	int answer;

	// verify input
	while (!(cin >> answer) || (answer != 0 && answer != 1)) 
	{	
		cout << "Wrong input! Press 1 to fortify or 0 to skip" << endl;
		cin.clear();
		cin.ignore (1000, '\n');
	}

	if (answer == 1)
		cout << "Player " << id << " moved X armies from country Y to country Z" << endl;
	else cout << "Player " << id << " chose not to fortify" << endl;
}

Player::~Player()
{
}
