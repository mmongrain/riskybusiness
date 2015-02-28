<<<<<<< HEAD
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
  std::vector<Player*> *get_players() { return &players; }

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
=======
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
};

#endif
>>>>>>> cadfb050949d9b4fff7a68d48259675877031a7b
