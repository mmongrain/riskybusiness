#include "player.h"
#include <iostream>


Player::Player(int i) {
	id = i;
}

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}

void Player::Reinforce() {
	std::cout << "\nReinforcement phase:\nPlayer " << id << " reinforced" << std::endl;
}

void Player::Attack() {
	int answer;
	std::cout << "\nAttack phase:\nPress 1 to attack or 0 to skip"<< std::endl;
	
	// verify input
	while (!(std::cin >> answer) || (answer != 0 && answer != 1)) 
	{	
		std::cout << "Wrong input! Press 1 to attack or 0 to skip" << std::endl;
		std::cin.clear();
		std::cin.ignore (1000, '\n');
	}

	if (answer == 1)
		std::cout << "Player " << id << " attacked country X from country Z" << std::endl;
	else std::cout << "Player " << id << " chose not to attack" << std::endl;
}

void Player::Move()
{
	std::cout << "\nFortification phase:\npress 1 to move or 0 to skip" << std::endl;
	int answer;

	// verify input
	while (!(std::cin >> answer) || (answer != 0 && answer != 1)) 
	{	
		std::cout << "Wrong input! Press 1 to fortify or 0 to skip" << std::endl;
		std::cin.clear();
		std::cin.ignore (1000, '\n');
	}

	if (answer == 1)
		std::cout << "Player " << id << " moved X armies from country Y to country Z" << std::endl;
	else std::cout << "Player " << id << " chose not to fortify" << std::endl;
}

Player::~Player()
{
}
