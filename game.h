#ifndef GAME_H_
#define GAME_H_

#include "player.h"
class Game {
public:
	Game();
	~Game();

	void PlayGame();

private:
  std::vector<Player*> players;
  bool game_over;
	int num_human_players;
	int num_comp_players;
	void Startup();
	void MainPhase();
	void AssignCountries();
  Map game_map;
};

#endif
