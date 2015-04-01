#ifndef CARD_H_
#define CARD_H_

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
    Player* get_owner() { return owner; }
    void set_owner(Player* new_owner);

  private:
    Player* owner;
    Type type;
};

#endif
