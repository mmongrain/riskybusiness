#ifndef GAME_H_
#define GAME_H_
#include "player.h"
#include "player_view.h"
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
    bool EndGame();
	void KillPlayer(Player* deadPlayer);
	void TestHelper();
	void TestHelper(int num_players);

    void set_game_over(bool value);
    bool get_game_over();
    std::vector<Player*> *get_players()     { return &players; }
    std::vector<Player*> get_copy_players() { return players; }
	std::vector<PlayerView*> *get_player_views()     { return &player_views; }  

    bool gui_mode;
    bool verbose_mode;

  private:
    std::vector<Player*> players;
	std::vector<PlayerView*> player_views;
    bool game_over;
    int num_human_players;
    int num_comp_players;

    void Startup();
	void LoadMap();
	void CreatePlayers();
	void AssignCountries();
	void MainPhase();
	void MainMenu();
    void Options();
    void PrintLogo();

	//void DefaultCompPlayers();
    //void CustomCompPlayers();
    //void ApplyStrategyChoice(int choice, CompPlayer* player);
};

#endif
