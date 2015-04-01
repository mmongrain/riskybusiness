#ifndef STATS_BATTLE_H_
#define STATS_BATTLE_H_

class Player;
class Stats;

class StatsBattle : public StatsDecorator {
  public:
    StatsBattle(Stats *decoratedStats);
    std::string get_stats_string();
    void UpdateStatsString();
    void Update();
  private:
    std::vector< std::pair<Player*, double> > player_win_ratio; 
}

#endif
