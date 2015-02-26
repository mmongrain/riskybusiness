#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Player; // does not "see" the Player class unless we forward declare it
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
     class Continent;
     class Territory {
      friend class Map;

      private:
        std::string name;
        int x;
        int y;
        Player *owner;
        int num_units;
        Continent *continent;
        std::vector<Territory*> adjacency_list; 

      public:
        std::string get_name() { return name; }
        std::string set_name(std::string name) {
          std::string temp = this->name;
          this->name = name;
          return temp;
        }

        int get_x()                { return x; }
        int get_y()                { return y; }
        Player *get_owner()        { return owner; }
        int get_units()        { return num_units; }
		void set_units(int u) { num_units = u; }
        Continent *get_continent() { return continent; }

        Player* set_owner(Player *owner) { 
          Player *temp = this->owner;
          this->owner = owner; 
          return temp;
        }

        int set_num_units(int num_units) {
          int temp = this->num_units;
          this->num_units = num_units;
          return temp;
        }

        std::vector<Territory*> get_adjacency_list() { return adjacency_list; }
        std::string ToString();
    };
  
    class Continent {
      friend class Map;
      private:
        std::string name;
        int victory_value;
        std::vector<Territory> territories;
        Player *owner;
      public:
        Player *getOwner() { return owner; }
        std::string get_name() { return name; }
        std::string set_name(std::string name) {
          std::string temp = this->name;
          this->name = name;
          return temp;
        }
        int get_victory_value() { return victory_value; }
        std::vector<Territory> get_territories() { return territories; }
        std::string ToString();
    };

  private:

    std::vector<Continent> continents;
    std::vector<Territory> territories;

    void ParseMapInfo(const std::vector<std::string> &section_map);
    void ParseContinentInfo(const std::vector<std::string> &section_continents);
    void ParseTerritoryInfo(const std::vector<std::string> &section_continents);
    void ReconcileTerritories();

  public:

    Map();
    Map(char* filename);
    void Load(char* filename);
    void Save(char* filename);

    std::string get_author() { return map_info.author; }
    std::string get_image()  { return map_info.image;  }
    bool get_wrap()          { return map_info.wrap;   }
    char get_scroll()        { return map_info.scroll; }
    bool get_warn()          { return map_info.warn;   }

    std::vector<Continent> get_continents()  { return continents; }
    std::vector<Territory> get_territories() { return territories; }
};

#endif
