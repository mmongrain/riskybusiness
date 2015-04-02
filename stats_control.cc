#include <string>
#include "game.h"
#include "stats_control.h"

StatsControl::StatsControl(Stats *decorated_stats) : StatsDecorator(decorated_stats) {
  std::vector<Player*> players = *(Game::Instance().get_players()); 
  num_territories = Map::Instance().get_territories()->size();
  if (num_territories) {
    for (Player* player : players) {
      double control = (double)player->get_num_territories() / (double)num_territories;
      control *= 100;
      player_control.push_back(PlayerDouble(player, control));
      player->AddObserver(this);
    }
  }
  UpdateStatsString();
}

void StatsControl::UpdateStatsString() {
  decorated_stats->UpdateStatsString();
  this->stats_string = decorated_stats->get_stats_string();
  std::string decoration = "\nMap control\n";
  for (PlayerDouble player_double : player_control) {
    decoration += player_double.first->get_name() + ": " + std::to_string(player_double.second) + "\%\n";
  }
  this->stats_string += decoration;
}

void StatsControl::Update() {
  for (PlayerDouble &player_double : player_control) {
    double control = ((double)player_double.first->get_num_territories()/(double)num_territories);
    control *= 100;
    player_double.second = control;
  }
  UpdateStatsString();
}
