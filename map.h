#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "continent.h"
#include "player.h"
#include "observer.h"
#include "territory.h"
#include <fstream>


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

    void Load(char* filename);
    void Save(char* filename);

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
	void ParseMapInfo(const std::vector<std::string> &section_map);
	void ParseContinentInfo(const std::vector<std::string> &section_continents);
	void ParseTerritoryInfo(const std::vector<std::string> &section_continents);

  private:

    struct MapInfo {
      std::string author;
      std::string image;
      bool wrap;
      char scroll;
      bool warn;
    } map_info;

    std::vector<Continent*> continents;
    std::vector<Territory*> territories;
    
    void Clear();
    

    void ReconcileTerritories();
    bool VerifyAdjacency(Territory* first, Territory* second);
    bool VerifyConnectivity();

};

#endif
