#ifndef UNIT_MAP_H
#define UNIT_MAP_H

#include <string>

#include "map.h"
#include "territory.h"
#include "continent.h"

class UnitMap {
  public:
    static void Instance();
    static void Load(char* filename);
    static void Save(char* filename);
    static void VerifyConnectivity(char* filename);
    static void StringToTerritory(char* filename, std::string s);
    static void StringToContinent(char* filename, std::string s);
};

#endif
