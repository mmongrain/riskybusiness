#include <vector>
#include <string>
#include <iostream>

#include "observer.h"
#include "map_view.h"
#include "map.h"

MapView::MapView(Map *map) { 
  this->map = map;
  map->AddObserver(this);
}

MapView::~MapView() {
  map->RemoveObserver(this);
}

void MapView::Update() {
  player = territories->get_owner();
  territory_units = this->Map::get_num_units();
  std::cout << this->to_string();
}

std::string MapView::to_string() {
  std::string out = "stuff";

  return out;
}
