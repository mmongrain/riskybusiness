#ifndef STATS_OBSERVER_H_
#define STATS_OBSERVER_H_

#include <string>

#include "observer.h"

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
