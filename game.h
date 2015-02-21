#pragma once
#include "Player.h"
class Game
{
public:
	Game();
	~Game();

	void PlayGame();

private:
	Player** players;
	bool game_over;
	int num_players;
	void Startup();
	void MainPhase();
	void AssignCountries();
};

