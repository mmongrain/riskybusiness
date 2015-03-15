#ifndef MAP_VIEW_H_
#define MAP_VIEW_H_

#include <string>
#include <vector>

#include "observer.h"
#include "player.h"
#include "map.h"

class MapView : Observer 
{
  public:
    MapView(Map *map); 
    ~MapView();
    void Update();
    std::string to_string();
  private:
    Map *map;
    std::vector<Territory*> territories;
	Player *player;
    int territory_units;
};

#endif
