// Header file for Country

#ifndef COUNTRY_H
#define COUNTRY_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Country
{
private:
	string countryName;
	string continent;
	string owner;
	int armySize;

public:
	void setContinent(string cont)
	{
		continent = cont;
	}
	void setCountryName(string name)
	{
		countryName = name;
	}
	void setOwner(string Owner)
	{
		//To be determined by the random generator
	}
	void setArmy(int size)
	{
		//To be determined by the Owner's armies
	}
	string getCountryName()
	{
		return countryName;
	}
	Country getCountryByName(string name);
};

#endif
