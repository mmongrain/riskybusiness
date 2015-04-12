#include <exception>
#include <typeinfo>
#include <iostream>
#include "exceptions.h"


BattleException::BattleException(){
}
const char * BattleException::what() const throw () {
	return typeid(*this).name();
}

CardException::CardException(){
}
const char * CardException::what() const throw () {
	return typeid(*this).name();
}

CardMatchException::CardMatchException(){
}
const char * CardMatchException::what() const throw () {
	return typeid(*this).name();
}

EmptyDeckException::EmptyDeckException(){
}
const char * EmptyDeckException::what() const throw() {
	return typeid(*this).name();
}
