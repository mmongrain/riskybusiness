#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Continents
{
private:
	string continent_name;
	vector<Continents> continent_vector;

public:
	string getContinent_Name()
	{
		return continent_name;
	}

	void setContinent_Name(string name)
	{
		continent_name = name;
	}
};