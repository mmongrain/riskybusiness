#include "comp_player.h"
#include "player.h"
#include <iostream>

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN (COMPUTER) ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}

void Player::Reinforce() {
	Player::Reinforce(); 
	std::cout << " (Computer)" << std::endl;
}

void Player::Attack() {
	std::cout << "Player " << id << " attacked (computer)" << std::endl;
}

void Player::Move() {
	std::cout << "Player " << id << " moved (computer)" << std::endl;
}