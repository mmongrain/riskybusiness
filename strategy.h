#ifndef STRATEGY_H_ 
#define STRATEGY_H_


class Strategy {
	virtual void attack() = 0;
};

class Aggressive : public Strategy {

};

#endif