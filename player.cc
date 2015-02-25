#include "player.h"
#include <iostream>
#include <vector>

Player::Player() {
  id = player_id++;
}

Player::~Player() {}

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}

int Player::player_id = 0;
