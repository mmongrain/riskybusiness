#include "game.h"
#include "player.h"
#include "player_view.h"
#include "human_player.h"
#include <vector>


/**
 * NOTE: Please don't comment out main() methods used for testing.
 * Exclude them from compilation using Build Actions in Visual Studio, or by
 * setting your own compilation settings in the makefile.
 **/

static const int NUM_PLAYERS = 8;

int main () {
  // Initialize the objects
  char FILENAME[100] = "World.map";
  Map::Instance().Load(FILENAME);
  Game::Instance().TestHelper(NUM_PLAYERS);

  // Create views for each player 
  std::vector<Player*> players = *(Game::Instance().get_players());
  std::vector<PlayerView*> player_views = *(new std::vector<PlayerView*>(NUM_PLAYERS));
  for (int i = 0; i < NUM_PLAYERS; i++) {
    player_views[i] = new PlayerView(players[i]);
  }

  // Change some fields, triggering NotifyObservers();
  for (int i = 0; i < players.size(); i++) {
    switch (i % 4) {
      case 0: players[i]->set_name("John");
              break;
      case 1: players[i]->set_name("Paul");
              break;
      case 2: players[i]->set_name("George");
              break;
      case 3: players[i]->set_name("Ringo");
              break;
    }
    players[i]->set_battles_won(i + 1);
    players[i]->set_reinforcements((i + 1) * 2);
    players[i]->set_total_units((i + 1) * 4);
    players[i]->remove_territory(players[i]->get_owned_territories()[0]);
  }

  // Delete 'em all
  for (int i = 0; i < NUM_PLAYERS; i++) {
    delete player_views[i];
  }
}


