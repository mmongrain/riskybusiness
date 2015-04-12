#include <exception>
#include <typeinfo>
#include <iostream>
#include "exceptions.h"


BattleException::BattleException(std::string error){
	std::cerr << error << std::endl;
}
const char * BattleException::what() const {
	return typeid(*this).name();
}

CardException::CardException(){
}
const char * CardException::what() const {
	return typeid(*this).name();
}

CardMatchException::CardMatchException(){
}
const char * CardMatchException::what() const {
	return typeid(*this).name();
}

EmptyDeckException::EmptyDeckException(){
}
const char * EmptyDeckException::what() const {
	return typeid(*this).name();
}
