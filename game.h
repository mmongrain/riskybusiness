#ifndef GAME_H_
#define GAME_H_

#include "player.h"
class Game {
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

#endif