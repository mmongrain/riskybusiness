#ifndef TERRITORY_H_
#define TERRITORY_H_

#include <string>
#include <vector>

#include "observer.h"

class Continent;
class Player;

class Territory : public Observable {

   public:

     int get_x()                { return x; }
     int get_y()                { return y; }
     std::string get_name()     { return name; }
     Player *get_owner()        { return owner; }
     int get_num_units()        { return num_units; }
     Continent *get_continent() { return continent; }

     std::string set_name(std::string name);
     int set_num_units(int num_units);
     Player* set_owner(Player *owner);
		 void set_continent(Continent *c) { continent = c; }

     std::vector<Territory*> *get_adjacency_list() { return &adjacency_list; }
     std::string ToString();
     bool AreAdjacent(Territory *bordering);
     bool CanAttack();
     bool CanFortify();
     std::vector<Territory*> GetAttackableTerritories(Player* player);
     std::vector<Territory*> GetAdjacentOwnedTerritories(Player* player);

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
