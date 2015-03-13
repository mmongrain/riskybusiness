#ifndef "TERRITORY_H_"
#define "TERRITORY_H_"

#include <string>
#include <vector>
#include "continent.h"
#include "player.h"
#include "map.h"

class Territory : Observable {

   public:

     std::string get_name() { return name; }
     std::string set_name(std::string name) {
       std::string temp = this->name;
       this->name = name;
       NotifyObservers();
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
     bool CanAttack();
     bool CanFortify();
     void PrintAdjacentTerritories();
     void PrintAttackableTerritories(Player *player);
     std::vector<Territory*> GetAttackableTerritories(Player* player);
     void PrintAdjacentOwnedTerritories(Player *player);
     std::vector<Map::Territory*> GetAdjacentOwnedTerritories(Player* player);

   private:

     friend class Map;
     std::string name;
     int x;
     int y;
     Player *owner;
     int num_units;
     Continent *continent;
     std::vector<Territory*> adjacency_list; 
};

#endif
