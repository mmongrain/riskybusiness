#ifndef STATS_DECORATOR_H_
#define STATS_DECORATOR_H_

#include "stats.h"

class StatsDecorator : public Stats {
  public:
    StatsDecorator(Stats *decoratedStats) {
      this->decoratedStats = decoratedStats;
    }
    void Update() {
      decoratedStats->Update();
    }
    std::string get_stats_string() {
      return decoratedStats->get_stats_string();
    }
    void UpdateStatsString() {
      decoratedStats->UpdateStatsString();
    }
  protected:
    Stats *decoratedStats;

};

#endif
