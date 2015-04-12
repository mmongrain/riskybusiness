#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

class BattleException : public std::exception {
public:
	BattleException();
	const char * what() const throw();
};

class CardException : public std::exception {
public:
	CardException();
	const char * what() const throw();
};

class CardMatchException : public std::exception {
public:
	CardMatchException();
	const char * what() const throw();
};

class EmptyDeckException : public std::exception {
public:
	EmptyDeckException();
	const char * what() const throw();
};


#endif

