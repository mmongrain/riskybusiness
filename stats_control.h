#ifndef STATS_CONTROL_H_
#define STATS_CONTROL_H_

#include <string>
#include <utility>
#include <vector>

#include "stats_decorator.h"

class Player;
class Stats;

class StatsControl : public StatsDecorator {
  public:
    typedef std::pair<Player*, double> PlayerDouble;
    StatsControl(Stats *decorated_stats);
    void UpdateStatsString();
    void Update();
  private:
    int num_territories;
    std::vector<PlayerDouble> player_control; 
};

#endif
