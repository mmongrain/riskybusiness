#ifndef MAP_H_
#define MAP_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "observer.h"

class Player;
class Map: public Observable { 

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
     class Territory : Observable {
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
       int get_num_units()        { return num_units; }
       Continent *get_continent() { return continent; }

       Player* set_owner(Player *owner) { 
         Player *temp = this->owner;
         this->owner = owner;
         NotifyObservers();
         return temp;
       }

       int set_num_units(int num_units) {
         int temp = this->num_units;
         this->num_units = num_units;
         NotifyObservers();
         return temp;
       }

       std::vector<Territory*> *get_adjacency_list() { return &adjacency_list; }
       std::string ToString();
       bool AreAdjacent(Territory *bordering);
       bool AttackIsValid(Territory *defending);
       void PrintAdjacentTerritories();
       void PrintAttackableTerritories(Player *player);
       void PrintAdjacentOwnedTerritories(Player *player);
    };
  
    class Continent : Observable {
      friend class Map;
      private:
        std::string name;
		    int bonus; // used to calculate reinforcements
        std::vector<Territory*> territories;
        Player *owner;
      public:
        Player *getOwner()     { return owner; }
        Player *setOwner(Player *new_owner) {
          Player *temp = owner;
          owner = new_owner;
          NotifyObservers();
          return temp;
        }
        std::string get_name() { return name; }
        std::string set_name(std::string name) {
          std::string temp = this->name;
          this->name = name;
          return temp;
        }
        int get_bonus() { return bonus; }
        std::vector<Territory*> &get_territories() { return territories; }
        std::string ToString();
    };

  private:

    std::vector<Continent*> continents;
    std::vector<Territory*> territories;


    void ParseMapInfo(const std::vector<std::string> &section_map);
    void ParseContinentInfo(const std::vector<std::string> &section_continents);
    void ParseTerritoryInfo(const std::vector<std::string> &section_continents);
    void ReconcileTerritories();

  public:
    // BEGIN SINGLETON GARBAGE, taken from 
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
    static Map &Instance() {
      static Map instance;
      return instance;
    }

    Map() {};
    Map(Map const&);
    void operator=(Map const&);
    // END SINGLETON GARBAGE

    void Load(char* filename);
    void Save(char* filename);

    Map::Territory* StringToTerritory(std::string s);

    std::string get_author() { return map_info.author; }
    std::string get_image()  { return map_info.image;  }
    bool get_wrap()          { return map_info.wrap;   }
    char get_scroll()        { return map_info.scroll; }
    bool get_warn()          { return map_info.warn;   }

    std::vector<Continent*> *get_continents()      { return &continents;  }
    std::vector<Territory*> *get_territories()     { return &territories; }
    std::vector<Territory*> get_copy_territories() { return territories;  }
};

#endif
