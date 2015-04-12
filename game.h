#ifndef GAME_H_
#define GAME_H_

#include <vector>

class Map;
class Player;

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
    static void GUIHelper();
    void EndGame();
	void KillPlayer(Player* deadPlayer);
	void TestHelper();
	void TestHelper(int num_players);

    void set_game_over(bool value);
    bool get_game_over();
    std::vector<Player*> *get_players()     { return &players; }
    std::vector<Player*> get_copy_players() { return players; }

    // Game options
    bool gui_mode;
    bool gui_labels;
    bool gui_authorinfo;
    bool verbose_mode;

  private:

    std::vector<Player*> players;
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
};

#endif
