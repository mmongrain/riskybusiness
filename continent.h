#ifndef CONTINENT_H_
#define CONTINENT_H_

#include <string>
#include <vector>

#include "map.h"
#include "observer.h"
#include "player.h"
#include "territory.h"


class Continent : public Observable {

  public:

    int get_bonus()         { return bonus; }
    std::string get_name()  { return name; }
    Player *get_owner()     { return owner; }

	void set_bonus(int b)	{ bonus = b; }
    std::string set_name(std::string name);
    Player *set_owner(Player *new_owner);
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
