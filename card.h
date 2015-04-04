#ifndef CARD_H_
#define CARD_H_

#include <string>

class Player;

class Card { 
  public:
    
    enum Type { 
      JOKER,
      SOLDIER,
      CAVALRY,
      CANNON
    };

    Card(Type _type) : type(_type) {}
    Type get_type() { return type; }
    std::string get_type_string();
    std::string get_card_string();
    Player* get_owner() { return owner; }
    void set_owner(Player* new_owner);

  private:
    Player* owner;
    Type type;
};

#endif
