#include "player.h"
#include <iostream>
#include <vector>

Player::Player(int i) {
	id = i;
}

void Player::PlayTurn() {
	std::cout << "\n\n=== PLAYER " << id << "'S TURN ==" << std::endl;
	Reinforce();
	Attack();
	Move();
}
