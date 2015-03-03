#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include "observer.h"

#include <vector>
#include <string>


class Player: public Observable {
  protected:
    int id;
    int victories;
    int reinforcements;
    int total_units;
    virtual void Reinforce();
    virtual void Attack() = 0;
    virtual void Move() = 0;

  private:
    static int player_id;
    std::string name;
    void DetermineContinentOwnership();

  public:
    Player(): total_units(0), reinforcements(0), victories(0), id(player_id++) {}
    virtual ~Player() {}
    virtual void PlayTurn();
    void PrintOwnedTerritories();
	void victory();
    //Map::Territory *StringToTerritory(std::string s); moved to map.cc
    Map::Territory *StringToOwnedTerritory(std::string s);

    void add_territory(Map::Territory *new_territory);
    void add_continent(Map::Continent *new_continent);
    void remove_territory(Map::Territory *old_territory);
    void remove_continent(Map::Continent *old_continent);

    /**
     * TODO: We have getters and setters for these members... should we make these
     * public members protected?   --Matthew 
	 * I think so -- Alika 
     **/
    std::vector<Map::Territory*> owned_territories;
    std::vector<Map::Continent*> owned_continents; 

    int get_id()             { return id; }
    int get_victories()      { return victories; }
    int get_reinforcements() { return reinforcements; }
    int get_total_units()    { return total_units; }
    std::string get_name()   { return name; }

    std::vector<Map::Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Map::Continent*> &get_owned_continents()  { return owned_continents; } 

    void set_victories(int victories);
    void set_reinforcements(int reinforcements);
    void set_total_units(int units);
    void set_name(std::string name);
};

#endif
