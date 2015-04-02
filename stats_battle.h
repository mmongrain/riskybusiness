#ifndef STATS_BATTLE_H_
#define STATS_BATTLE_H_

#include <string>
#include <utility>
#include <vector>

#include "stats_decorator.h"

class Player;
class Stats;

class StatsBattle : public StatsDecorator {
  public:
    typedef std::pair<Player*, double> PlayerDouble;
    StatsBattle(Stats *decorated_stats);
    void UpdateStatsString();
    void Update();
  private:
    std::vector<PlayerDouble> player_win_ratio; 
};

#endif
