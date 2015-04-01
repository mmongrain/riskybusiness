#ifndef STATS_CONTROL_H_
#define STATS_CONTROL_H_

#include <string>
#include <vector>

#include "stats_decorator.h"

class Player;
class Stats;

class StatsControl : public StatsDecorator {
  public:
    typedef std::pair<Player*, double> PlayerDouble;
    StatsControl(Stats *decoratedStats);
    std::string get_stats_string();
    void UpdateStatsString();
    void Update();
  private:
    int num_territories;
    std::vector< std::pair<Player*, double> > player_control; 
}

#endif
