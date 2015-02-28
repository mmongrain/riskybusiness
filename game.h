#ifndef GAME_H_
#define GAME_H_

#include "player.h"
class Game {
public:
  // BEGIN SINGLETON, modeled from 
  // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
  static Game &Instance() {
    static Game instance;
    return instance;
  }

  Game() {}
  Game(Map const&) = delete;
  void operator=(Game const&) = delete;
  // END SINGLETON
  
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
};

#endif
