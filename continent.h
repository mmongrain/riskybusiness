// Header for Continent

#ifndef CONTINENT_H
#define CONTINENT_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Continent
{
private:
		string continentName;
public:
	void setContinentName(string name)
	{
		continentName = name;
	}
};

#endif