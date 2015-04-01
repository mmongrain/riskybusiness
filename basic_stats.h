#ifndef BASIC_STATS_H_
#define BASIC_STATS_H_

#include <string>
#include <vector>
#include <utility> // std::pair

#include "stats.h"

class Player;

class BasicStats : public Stats {
  public:
    BasicStats();
    ~BasicStats();
    typedef std::pair<Player*, int> PlayerInt;
    void Update();
    std::string get_stats_string() { return stats_string; } 

  protected:
    void UpdateStatsString();
    std::vector<PlayerInt> player_total_territories;
    std::vector<PlayerInt> player_total_units;
    std::vector<PlayerInt> player_total_cards;
};

#endif
