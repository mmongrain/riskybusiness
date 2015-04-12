#ifndef STATS_BASIC_H_
#define STATS_BASIC_H_

#include <vector>
#include <utility>

#include "stats.h"

class Player;

class StatsBasic : public Stats {

  public:

    StatsBasic();
    ~StatsBasic();
    typedef std::pair<Player*, int> PlayerInt;
    virtual void Update();

  protected:
    
    virtual void UpdateStatsString();
    std::vector<PlayerInt> player_total_territories;
    std::vector<PlayerInt> player_total_units;
    std::vector<PlayerInt> player_total_cards;
};

#endif
