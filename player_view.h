#ifndef PLAYER_VIEW_H_
#define PLAYER_VIEW_H_

#include <string>
#include <vector>

#include "continent.h"
#include "map.h"
#include "observer.h"
#include "player.h"
#include "territory.h"

class PlayerView : Observer {
  public:
    PlayerView(Player *player); 
    ~PlayerView();
    void Update();
    std::string to_string();
  private:
    Player *player; 
    std::vector<Territory*> territories;
    std::vector<Continent*> continents;
    int reinforcements;
    int units;
    int victories;
};

#endif
