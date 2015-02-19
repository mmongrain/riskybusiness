#ifndef CONTINENT_H_
#define CONTINENT_H_

#include <string>
#include <iostream>
#include <vector>
#include <list>

class Continent
{
private:
  std::string continentName;
public:
	void setContinentName(std::string name)
	{
		continentName = name;
	}
};

#endif
