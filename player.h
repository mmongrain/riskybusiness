#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

#include "map.h"
#include "observer.h"

class Player: public Observable {
  protected:
    int id;
    int victories;
    int reinforcements;
    int units;
	virtual void Reinforce();
    virtual void Attack() = 0;
    virtual void Move() = 0;

  private:
    static int player_id;
    std::string name;

  public:
    Player();
    virtual ~Player();
    virtual void PlayTurn();

    void add_territory(Map::Territory *new_territory);
    void add_continent(Map::Continent *new_continent);
    void remove_territory(Map::Territory *old_territory);
    void remove_continent(Map::Continent *old_continent);

    /**
     * TODO: We have getters and setters for these members... should we make these
     * public members protected?   --Matthew
     **/
    std::vector<Map::Territory *> owned_territories;
    std::vector<Map::Continent *> owned_continents;

    int get_id()             { return id; }
    int get_victories()      { return victories; }
    int get_reinforcements() { return reinforcements; }
    int get_units()          { return units; }
    std::string get_name()   { return name; }

    std::vector<Map::Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Map::Continent*> &get_owned_continents()  { return owned_continents; } 

    void set_victories(int victories);
    void set_reinforcements(int reinforcements);
    void set_units(int units);
    void set_name(std::string name);
};

#endif
