#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <vector>

#include "observer.h"

class Continent;
class Territory;
class Player;

class Map: public Observable { 

  public:

    // BEGIN SINGLETON
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static Map &Instance() {
      static Map instance;
      return instance;
    }

    Map() {};
    Map(Map const&);
    void operator=(Map const&);
    // END SINGLETON 

    bool Load(const char* filename);
    void Save(const char* filename);
    bool VerifyConnectivity();

    Territory* StringToTerritory(std::string s);
    Continent* StringToContinent(std::string s);

    std::string get_author() { return map_info.author; }
    std::string get_image()  { return map_info.image;  }
    bool get_wrap()          { return map_info.wrap;   }
    char get_scroll()        { return map_info.scroll; }
    bool get_warn()          { return map_info.warn;   }

    std::vector<Continent*> *get_continents()      { return &continents;  }
    std::vector<Territory*> *get_territories()     { return &territories; }
    std::vector<Territory*> get_copy_territories() { return territories;  }


  private:

    // So that MapEditor can freely modify datamembers
    friend class MapEditor;

    struct MapInfo {
      std::string filename;
      std::string author;
      std::string image;
      bool wrap;
      char scroll;
      bool warn;
    } map_info;

    std::vector<Continent*> continents;
    std::vector<Territory*> territories;
    
    void Clear();
    bool ParseMapInfo(const std::vector<std::string> &section_map);
    bool ParseContinentInfo(const std::vector<std::string> &section_continents);
    bool ParseTerritoryInfo(const std::vector<std::string> &section_continents);
    bool ReconcileTerritories();
    bool VerifyAdjacency(Territory* first, Territory* second);

};

#endif
