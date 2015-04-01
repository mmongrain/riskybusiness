#include <string>
#include "game.h"
#include "stats_control.h"

StatsControl::StatsControl(Stats *decoratedStats) : StatsDecorator(decoratedStats) {
  std::vector<Player*> players = *(Game::Instance().get_players()); 
  num_territories = Map::Instance().get_territories()->size();
  for (Player* player : players) {
    double control = ((double)player->get_num_territories())/((double)num_territories);
    player_control.push_back(PlayerDouble(player, control));
  }
  UpdateStatsString();
}

void StatsControl::UpdateStatsString() {
  decoratedStats->UpdateStatsString();
  std::string decoration = "\nTerritory control\n";
  for (PlayerDouble player_double : player_control) {
    decoration += player_double.first->get_name() + ": " + std::to_string(player_double.second) + "\n";
  }
  this->stats_string += decoration;
}

void StatsControl::Update() {
  decoratedStats->Update();
  for (PlayerDouble player_double : player_control) {
    double control = ((double)player_double.first->get_num_territories()/(double)num_territories);
    player_double.second = control;
  }
  UpdateStatsString();
}
