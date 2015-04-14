#ifndef strategy_h
#define strategy_h

class Player;
class Territory;

class Strategy {
    
  public:

    virtual void Reinforce(Player *player, int reinforcments);
    virtual void Attack(Player *player) = 0;
    virtual void Fortify(Player *player);
    virtual ~Strategy(){};

    virtual int GetNumConqueringArmies(int min, int max, Territory* attacking, Territory* defending);
    virtual bool AutoAttackChoice();

  protected:

    bool WillAttack();
    Territory* FromWhereToAttack(Player* player);
    Territory* WhomToAttack(Player* player, Territory* attacking);
    bool WantsToAutoAttack(); 
    int NumConqueringArmiesToMove(int min, int max);
    bool WillFortify();
    Territory* ChoosePointOfDepart(Player *player);
    Territory* ChooseDestination(Player *player, Territory* move_from);
};

#endif
