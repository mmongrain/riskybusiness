#include <vector>
#include <string>

#include "game.h"
#include "stats_battle.h"

StatsBattle::StatsBattle(Stats *decorated_stats) : StatsDecorator(decorated_stats) {
  std::vector<Player*> players = *(Game::Instance().get_players()); 
  for (Player* player : players) {
    int wins = player->get_battles_won();
    int losses = player->get_battles_lost();
    int battles = wins + losses;
    double ratio;
    if (battles) {
      ratio = (double)wins / (double)battles;
      ratio *= 100;
    } else {
      ratio = 0.0;
    }
    player_win_ratio.push_back(PlayerDouble(player, ratio));
    player->AddObserver(this);
  }
  UpdateStatsString();
}

void StatsBattle::UpdateStatsString() {
  this->stats_string = decorated_stats->get_stats_string();
  std::string decoration = "\n\% Battles won:\n";
  for (PlayerDouble player_double : player_win_ratio) {
    decoration += player_double.first->get_name() + ": " + std::to_string(player_double.second) + "\%\n";
  }
  this->stats_string += decoration;
}

void StatsBattle::Update() {
  decorated_stats->Update();
  for (PlayerDouble &player_double : player_win_ratio) {
    int wins = player_double.first->get_battles_won();
    int losses = player_double.first->get_battles_lost();
    int battles = wins + losses;
    double ratio;
    if (battles) {
      ratio = (double)wins / (double)battles;
      ratio *= 100;
    } else {
      ratio = 0.0;
    }
    player_double.second = ratio;
  }
  UpdateStatsString();
}
