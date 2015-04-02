#include <stdlib.h>
#include <iostream>

#include "map.h"
#include "game.h"
#include "stats.h"
#include "stats_basic.h"
#include "stats_battle.h"
#include "stats_control.h"

int NUM_PLAYERS = 4;

int main() {
  // Load a map
  srand(time(NULL));
  char FILENAME[100] = "World.map";
  Map::Instance().Load(FILENAME);

  // Loads the game. TestHelper generates some default players,
  // assigns them randomly the countries on the map, and populates the players
  // with dummy data.
  Game::Instance().TestHelper(NUM_PLAYERS);

  // Create a stats object, print it, decorate it, print it, rinse, and repeat.
  // TestHelper() generates new dummy data, triggering observer Update()s.
  Stats *stats = new StatsBasic();
  std::cout << stats->get_stats_string() << std::endl;
  stats = new StatsControl(stats);
  Game::Instance().TestHelper();
  std::cout << stats->get_stats_string() << std::endl;
  stats = new StatsBattle(stats);
  Game::Instance().TestHelper();
  std::cout << stats->get_stats_string() << std::endl;
}
