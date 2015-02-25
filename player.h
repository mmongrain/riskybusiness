#ifndef PLAYER_H_
#define PLAYER_H_
#include "map.h"
#include <vector>


class Player : Observable {

  public:
    Player(int i);
    virtual ~Player();
    virtual void PlayTurn();
    std::vector<Map::Territory *> owned_territories;
    std::vector<Map::Continent *> owned_continents;

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
