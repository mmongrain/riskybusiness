#ifndef strategy_h
#define strategy_h

class Player;

class Strategy {
public:
	virtual void Reinforce(Player *player, int reinforcements) = 0;
	virtual void Attack(Player *player) = 0;
	virtual void Fortify(Player *player) = 0;
	virtual ~Strategy(){};
};

#endif
