#include <iostream>
#include <string>
#include <vector>
#include "continents.h"

using namespace std;

class Country
{
private:
	int x_coord;
	int y_coord;
	int army_size;
	int id_num;

	string country_name;
	string owner;
	Continents continent; //need to include continents file

	vector<Country> adjacent_country;
	vector<Country> country_vector;

public:
	Country(){x_coord=0; y_coord=0; country_name="country"; id_num=0;} 

	int getX_Coord()
	{
		return x_coord;
	}
	int getY_Coord()
	{
		return y_coord;
	}
	int getArmy_Size()
	{
		return army_size;
	}
	string getCountry_Name()
	{
		return country_name;
	}
	string getOwner()
	{
		return owner;
	}
	Continents getContinent()
	{
		return continent;
	}

	//setters
	void setX_Coord(int x)
	{
		x_coord = x;
	}
	void setY_Coord(int y)
	{
		y_coord = y;
	}
	void setArmy_Size(int size)
	{
		army_size = size;
	}
	void setCountry_Name(string name)
	{
		country_name = name;
	}
	void setOwner(string own)
	{
		owner = own;
	}

	//Figure out c++ way
	void addAdjacentCountry(Country adjacentCountry);

};
