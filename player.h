#ifndef PLAYER_H_
#define PLAYER_H_

#include <SFML/Graphics.hpp>
#include <deque>
#include <vector>
#include <string>

#include "observer.h"

class Territory;
class Continent;
class Card;

class Player : public Observable {

  public:

    Player();
    virtual ~Player();
    
    void CardsHandler();
    virtual void PlayTurn();
    void TransferHand(Player* winner);

    std::vector<Territory*> AttackingTerritories();
    std::vector<Territory*> AttackableTerritories(Territory* attacking);
    std::vector<Territory*> FortifyingTerritories();
    std::vector<Territory*> FortifiableTerritories(Territory* source);

    void add_territory(Territory *new_territory);
    void add_continent(Continent *new_continent);
    void add_card(Card *new_card);
    void remove_territory(Territory *old_territory);
    void remove_continent(Continent *old_continent);
    void remove_card(Card *old_card);

    int get_battles_won()     { return battles_won; }
    int get_battles_lost()    { return battles_lost; }
    sf::Color get_color()     { return color; }
    int get_id()              { return id; }
    int get_reinforcements()  { return reinforcements; }
    int get_num_cards()       { return hand.size(); }
    int get_total_units()     { return total_units; }
    int get_num_territories() { return owned_territories.size(); }
    bool get_card_this_turn() { return card_this_turn; }
    std::string get_name()    { return name; }

    std::vector<Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Continent*> &get_owned_continents()  { return owned_continents; } 
    std::deque<Card*>       &get_hand()              { return hand; }
    std::vector<int>        &get_last_roll()         { return last_roll; }

    void set_battles_won(int battles_won);
    void set_battles_lost(int battles_lost);
    void set_reinforcements(int reinforcements);
    void set_total_units(int units);
    void set_name(std::string name);
    void set_card_this_turn(bool card_this_turn);
    void set_last_roll(std::vector<int> last_roll);

  protected:

    std::vector<Territory*> owned_territories;
    std::vector<Continent*> owned_continents; 
    int id;
    int reinforcements;
    int total_units;
    int battles_won;
    int battles_lost;
    int bonus_reinforcements;
    bool card_this_turn;
    int times_redeemed;
    std::vector<int> last_roll;
    std::deque<Card*> hand;
    sf::Color color;
    virtual void Reinforce() = 0;
    virtual void Attack() = 0;
    virtual void Fortify() = 0;
    void CalculateReinforcements();
    void Draw();
    std::string HasMatch();
    void Match();

  private:

    static int player_id;
    std::string name;
    void DetermineContinentOwnership();

};

#endif
