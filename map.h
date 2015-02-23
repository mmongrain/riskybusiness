#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Map { 

  private:

    struct MapInfo {
      std::string author;
      std::string image;
      bool wrap;
      char scroll;
      bool warn;
    } map_info;

  public:

    struct Territory {
      friend class Map;
      private:
        std::string name;
        int x;
        int y;
        std::string continent;
        std::vector<std::string> adjacency_list;
      public:
        std::string get_name() { return name; }
        int get_x() { return x; }
        int get_y() { return y; }
        std::string get_continent() { return continent; }
        std::vector<std::string> get_adjacency_list() { return adjacency_list; }
        std::string ToString();
    };
  
    struct Continent {
      friend class Map;
      private:
        std::string name;
        int victory_size;
        std::vector<Territory> territories;
      public:
        std::string get_name() { return name; }
        int get_victory_size() { return victory_size; }
        std::vector<Territory> get_territories() { return territories; }
        std::string ToString();
    };

  private:

    std::vector<Continent> continents;
    std::vector<Territory> territories;

    void ParseMapInfo(const std::vector<std::string> &section_map);
    void ParseContinentInfo(const std::vector<std::string> &section_continents);
    void ParseTerritoryInfo(const std::vector<std::string> &section_continents);

  public:

    Map();
    Map(char* filename);
    void Load(char* filename);
    void Save(char* filename);

    std::string get_author() { return map_info.author; }
    std::string get_image()  { return map_info.image; }
    bool get_wrap()          { return map_info.wrap; }
    char get_scroll()        { return map_info.scroll; }
    bool get_warn()          { return map_info.warn; }

    std::vector<Continent> get_continents()  { return continents; }
    std::vector<Territory> get_territories() { return territories; }
};

#endif