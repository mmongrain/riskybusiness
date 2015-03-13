#ifndef "CONTINENT_H_"
#define "CONTINENT_H_"

#include <string>
#include <vector>

#include "map.h"
#include "player.h"
#include "territory.h"


class Continent : Observable {

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
      NotifyObservers();
      return temp;
    }
    int get_bonus() { return bonus; }
    std::vector<Territory*> &get_territories() { return territories; }
    std::string ToString();

  private:

    friend class Map;
    std::string name;
    int bonus; // used to calculate reinforcements
    std::vector<Territory*> territories;
    Player *owner;
};

#endif
