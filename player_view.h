#ifndef PLAYER_VIEW_H_
#define PLAYER_VIEW_H_

#include <string>
#include <vector>

#include "observer.h"

class Player;
class Territory;
class Continent;

class PlayerView : Observer {
  public:
    PlayerView(Player *player); 
    ~PlayerView();
    void Update();
    std::string to_string();
    std::string get_view_str() { return view_str; }
  private:
    Player *player; 
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;
    std::string view_str;
    int reinforcements;
    int total_units;
    int battles_won;
    int battles_lost;
};

#endif
