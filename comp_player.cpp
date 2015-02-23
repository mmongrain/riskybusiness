#include "comp_player.h"
#include "player.h"
#include "strategy.h"
#include <iostream>

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN (COMPUTER) ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}

void Player::Reinforce() {
	Player::Reinforce(); 
	std::cout << "Player " << id << " reinforced (computer)" << std::endl;
}

void Player::Attack() {
	CompPlayer::strategy->attack();  // doesn't work... gotta figure out why
	std::cout << "Player " << id << " attacked (computer)" << std::endl;
}

void Player::Move() {
	std::cout << "Player " << id << " moved (computer)" << std::endl;
}