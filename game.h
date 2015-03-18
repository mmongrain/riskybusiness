#ifndef GAME_H_
#define GAME_H_
#include "player.h"
#include "comp_player.h"

class Game {
  public:

    // BEGIN SINGLETON, modeled from 
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static Game &Instance() {
      static Game instance;
      return instance;
    }

    Game() {};
    Game(Map const&);
    void operator=(Game const&);
    // END SINGLETON
    ~Game() {}

    static void PlayGame();
	void EndGame();
	void set_game_over(bool value);
	bool get_game_over();
    std::vector<Player*> *get_players()     { return &players; }
    std::vector<Player*> get_copy_players() { return players; }
	void killPlayer(Player* deadPlayer);

    void PlayerViewTestHelper(int num_players);

  private:
    std::vector<Player*> players;
    bool game_over;
    int num_human_players;
    int num_comp_players;
    void Startup();
    void PrintLogo();
    void MainPhase();
    void AssignCountries();
    void DefaultCompPlayers();
    void CustomCompPlayers();
    void ApplyStrategyChoice(int choice, CompPlayer* player);
};

#endif
