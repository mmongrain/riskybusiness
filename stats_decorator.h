#ifndef STATS_DECORATOR_H_
#define STATS_DECORATOR_H_

#include "stats.h"

class StatsDecorator : public Stats {
  public:
    StatsDecorator(Stats *decorated_stats) {
      this->decorated_stats = decorated_stats;
    }
    void Update() {
      decorated_stats->Update();
    }
    std::string get_stats_string() {
      return decorated_stats->get_stats_string();
    }
    void UpdateStatsString() {
      decorated_stats->UpdateStatsString();
    }
  protected:
    Stats *decorated_stats;

};

#endif
