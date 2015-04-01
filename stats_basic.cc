#include <vector>
#include <utility>

#include "stats_basic.h"
#include "player.h"
#include "game.h"

StatsBasic::StatsBasic() {
  std::vector<Player*> players = *(Game::Instance().get_players());
  for (Player* player : players) {
    player_total_territories.push_back(PlayerInt(player, player->get_num_territories()));
    player_total_units.push_back(PlayerInt(player, player->get_total_units()));
    player_total_cards.push_back(PlayerInt(player, player->get_num_cards()));
    player->AddObserver(this);
  }
  UpdateStatsString();
}

StatsBasic::~StatsBasic() {
  std::vector<Player*> players = *(Game::Instance().get_players());
  for (Player* player : players) {
    player->RemoveObserver(this);
  }
}

void StatsBasic::Update() {
  for (PlayerInt player_int : player_total_territories) {
    player_int.second = player_int.first->get_num_territories();
  }
  for (PlayerInt player_int : player_total_units) {
    player_int.second = player_int.first->get_total_units();
  }
  for (PlayerInt player_int : player_total_cards) {
    player_int.second = player_int.first->get_num_cards();
  }
  UpdateStatsString();
}

void StatsBasic::UpdateStatsString() {
  std::string new_stats_string;
  new_stats_string += "Territory Control:\n";
  for (PlayerInt player_int : player_total_territories) {
    new_stats_string += player_int.first->get_name() + ": " + std::to_string(player_int.second) + "\n";
  }
  new_stats_string += "\nUnit Control:\n";
  for (PlayerInt player_int : player_total_units) {
    new_stats_string += player_int.first->get_name() + ": " + std::to_string(player_int.second) + "\n";
  }
  new_stats_string += "\nCard Control:\n";
  for (PlayerInt player_int : player_total_cards) {
    new_stats_string += player_int.first->get_name() + ": " + std::to_string(player_int.second) + "\n";
  }
  stats_string = new_stats_string;
}

    
