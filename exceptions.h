#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_

#include <string>

class BattleException : public std::exception {
public:
	BattleException(std::string error);
	const char * what() const;
};

class CardException : public std::exception {
public:
	CardException();
	const char * what() const;
};

class CardMatchException : public std::exception {
public:
	CardMatchException();
	const char * what() const;
};

class EmptyDeckException : public std::exception {
public:
	EmptyDeckException();
	const char * what() const;
};


#endif

