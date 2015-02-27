#include "player.h"
#include "player_view.h"
#include "human_player.h"

/*

int main () {
  // Initialize the objects
  Player *player = new HumanPlayer();
  PlayerView *player_view = new PlayerView(player);

  // Make a couple of dummy continents and territories;
  Map::Territory* canada = new Map::Territory;
  canada->set_name("Canada");
  Map::Territory* russia = new Map::Territory;
  russia->set_name("Russia");
  Map::Continent* asia = new Map::Continent;
  asia->set_name("Asia");

  // Change some members, which will call NotifyObservers()
  player->set_name("Paul");
  player->set_victories(3);
  player->set_reinforcements(7);
  player->set_total_units(12);
  player->add_territory(canada);
  player->add_territory(russia);
  player->add_continent(asia);
  player->remove_territory(russia);

  // Delete 'em all
  delete player;
  delete player_view;
  delete canada;
  delete russia;
  delete asia;
}

*/