#ifndef strategy_h
#define strategy_h

class CompPlayer;

class Strategy {
public:
	virtual void execute(CompPlayer *c_player) = 0;
	virtual ~Strategy(){};
};

#endif
