#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include <vector>


class Player : Observable {
  public:
    Player(int i);
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

    std::vector<Map::Territory*> &get_owned_territories { return owned_territories; }
    std::vector<Map::Continent*> &get_owned_continents  { return owned_continents; } 

  protected:
    int id;
    int victories;
    int reinforcements;
    int armies;
    virtual void Reinforce() = 0;
    virtual void Attack() = 0;
    virtual void Move() = 0;
};

#endif
