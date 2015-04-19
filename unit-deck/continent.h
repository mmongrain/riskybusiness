#ifndef CONTINENT_H_
#define CONTINENT_H_

#include <string>
#include <vector>

#include "observer.h"

class Map;
class Player;
class Territory;

class Continent : public Observable {

  public:

    int get_bonus()         { return bonus; }
    std::string get_name()  { return name; }
    Player *get_owner()     { return owner; }

    std::string set_name(std::string name);
    Player *set_owner(Player *new_owner);
    std::vector<Territory*> &get_territories() { return territories; }
    std::string ToString();

  private:

    friend class Map;
    friend class MapEditor;
    std::string name;
    int bonus; // used to calculate reinforcements
    std::vector<Territory*> territories;
    Player *owner;
};

#endif
