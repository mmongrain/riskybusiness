#include <string>
#include "game.h"
#include "stats_control.h"

StatsControl(Stats *decoratedStats) : StatsDecorator(decoratedStats) {
  std::vector<Player*> players = *(Game::Instance()->get_players()); 
  num_territories = Map::Instance()->get_territories().size();
  for (Player* player : players) {
    double control = ((double)player->get_num_territories())/((double)num_territories);
    player_control.push_back(PlayerDouble(player, control));
  }
  UpdateStatsString();
}

std::string get_stats_string();
void UpdateStatsString();
void Update();
