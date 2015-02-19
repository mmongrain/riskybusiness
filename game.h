#pragma once
#include "Player.h"
class Game
{
public:
	Game();
	~Game();

	void playGame();

private:
	Player** players;
	bool game_over;
	int numOfPlayers;
	void startup();
	void Game::mainPhase();
	void assignCountries();
};

