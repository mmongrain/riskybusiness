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
	for(auto &territory : territories)
	{
		territory->ToString();
	}
}