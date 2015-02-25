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
    int armies;
    virtual void Reinforce() = 0;
    virtual void Attack() = 0;
    virtual void Move() = 0;

  private:
    static int player_id;
    std::string name;

  public:
    Player();
    virtual ~Player();
    virtual void PlayTurn();
    /**
     * TODO: We have getters and setters for the methods... should we make these
     * public members protected?   --Matthew
     **/
    std::vector<Map::Territory *> owned_territories;
    std::vector<Map::Continent *> owned_continents;

    int get_id()             { return id; }
    int get_victories()      { return victories; }
    int get_reinforcements() { return reinforcements; }
    int get_armies()         { return armies; }
    std::string get_name()   { return name; }

    std::vector<Map::Territory*> &get_owned_territories() { return owned_territories; }
    std::vector<Map::Continent*> &get_owned_continents()  { return owned_continents; } 

    void set_reinforcements(int reinfocements) { this->reinforcements = reinforcements; }
    void set_armies(int armies)                { this->armies = armies; }
    void set_name(std::string name)            { this->name = name; }
};

#endif
