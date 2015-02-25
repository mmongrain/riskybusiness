#ifndef PLAYER_VIEW_H_
#define PLAYER_VIEW_H_

#include <string>
#include <vector>

#include "observer.h"

class PlayerView : Observer {
  public:
    PlayerView(Player player); 
    ~PlayerView();
    void Update();
    std::string to_string();
  private:
    Player* player; 
    std::vector<Map::Territory> territories;
    std::vector<Map::Continent> continents;
    int reinforcements;
    int armies;
    int battles;
};

#endif
