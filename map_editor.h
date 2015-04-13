#ifndef _MAP_EDITOR_H
#define _MAP_EDITOR_H

#include <stdio.h>
#include <iostream>
#include <string>
#include "map.h"

class MapEditor {
    
public:
    MapEditor();
    static void introMapEditor();
    static void theMapEditor();
    static void TerritoryCreator();
    static void AdjacencyDefiner();
    static void ContinentCreator();
    static void AssignTerritoriesToContinent(Continent* newContinent);
		static bool VerifyMapCorrectness();

    
    
};

#endif
