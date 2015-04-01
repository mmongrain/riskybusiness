#include "map.h"
#include "game.h"
#include "stats.h"
#include "stats_basic.h"
#include "stats_control.h"

int main() {
  int NUM_PLAYERS = 4;
  char FILENAME[100] = "World.map";
  Map::Instance().Load(FILENAME);
  Game::Instance().PlayerViewTestHelper(NUM_PLAYERS);
  Stats *stats = new StatsBasic();
  std::cout << stats->get_stats_string();
  stats = new StatsControl(stats);
  std::cout << stats->get_stats_string();
}
  
