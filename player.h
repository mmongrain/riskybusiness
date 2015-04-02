#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "observer.h"

class Card;
class Territory;
class Continent;

class Player : public Observable {

  public:

    Player();
    virtual ~Player() {}
    virtual void PlayTurn();
    void PrintOwnedTerritories();
    void victory();
    Territory *StringToOwnedTerritory(std::string s);

    virtual bool WantsToAutoAttack() = 0;
    void add_territory(Territory *new_territory);
    void add_continent(Continent *new_continent);
    void add_card(Card *new_card);
    void remove_territory(Territory *old_territory);
    void remove_continent(Continent *old_continent);
    void remove_card(Card *old_card);
    void CaptureTerritory(Territory* attacking, Territory* defending, int min, int max);
    virtual int NumConqueringArmiesToMove(int min, int max) = 0;

    /**
     * TODO: We have getters and setters for these members... should we make these
     * public members protected?   --Matthew 
     * I think so -- Alika 
     **/
    std::vector<Territory*> owned_territories;
    std::vector<Continent*> owned_continents; 

    int get_battles_won()     { return battles_won; }
    int get_battles_lost()    { return battles_lost; }
    sf::Color get_color()     { return color; }
    int get_id()              { return id; }
    int get_reinforcements()  { return reinforcements; }
    int get_num_cards()       { return hand.size(); }
    int get_total_units()     { return total_units; }
    int get_num_territories() { return owned_territories.size(); }
    std::string get_name()    { return name; }

    std::vector<Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Continent*> &get_owned_continents()  { return owned_continents; } 

    void set_battles_won(int battles_won);
    void set_battles_lost(int battles_lost);
    void set_reinforcements(int reinforcements);
    void set_total_units(int units);
    void set_name(std::string name);

  protected:

    int id;
    int reinforcements;
    int total_units;
    int battles_won;
    int battles_lost;
    std::vector<Card*> hand;
    sf::Color color;
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
