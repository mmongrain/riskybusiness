#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include <string>

#include "continent.h"
#include "map.h"
#include "observer.h"
#include "territory.h"


class Player : public Observable {

  public:

    Player(): total_units(0), reinforcements(0), victories(0), id(player_id++) {}
    virtual ~Player() {}
    virtual void PlayTurn();
    void PrintOwnedTerritories();
    void victory();
    Territory *StringToOwnedTerritory(std::string s);

    virtual bool WantsToAutoAttack() = 0;
    void add_territory(Territory *new_territory);
    void add_continent(Continent *new_continent);
    void remove_territory(Territory *old_territory);
    void remove_continent(Continent *old_continent);
    void CaptureTerritory(Territory* attacking, Territory* defending, int min, int max);
    virtual int NumConqueringArmiesToMove(int min, int max) = 0;

    /**
     * TODO: We have getters and setters for these members... should we make these
     * public members protected?   --Matthew 
	 * I think so -- Alika 
     **/
    std::vector<Territory*> owned_territories;
    std::vector<Continent*> owned_continents; 

    int get_id()             { return id; }
    int get_victories()      { return victories; }
    int get_reinforcements() { return reinforcements; }
    int get_total_units()    { return total_units; }
    std::string get_name()   { return name; }

    std::vector<Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Continent*> &get_owned_continents()  { return owned_continents; } 

    void set_victories(int victories);
    void set_reinforcements(int reinforcements);
    void set_total_units(int units);
    void set_name(std::string name);

  protected:

    int id;
    int victories;
    int reinforcements;
    int total_units;
    virtual void Reinforce() = 0;
    virtual void Attack() = 0;
    virtual void Fortify() = 0;
    void CalculateReinforcements();

  private:

    static int player_id;
    std::string name;
    void DetermineContinentOwnership();

};

#endif
