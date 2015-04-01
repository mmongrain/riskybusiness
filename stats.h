#ifndef STATS_OBSERVER_H_
#define STATS_OBSERVER_H_

#include <string>
#include <vector>
#include <utility> // std::pair

#include "observer.h"

class Player;

class Stats : public Observer {
  public:
    virtual ~Stats() {}
    virtual void Update() {} 
    std::string get_stats_string() { return stats_string; } 
    virtual void UpdateStatsString() = 0;

  protected:
    std::string stats_string;
};

#endif
