#ifndef COUNTRY_H_
#define COUNTRY_H_

#include <iostream>
#include <vector>
#include <list>


class Country {
private:
  std::string country_name;
  std::string continent;
  std::string owner;
  int army_size;

public:
  void set_continent(std::string cont) { continent = cont; }
  void set_country_name(std::string name) { country_name = name; }
  void set_owner(std::string owner) {}
  void set_army(int size) {}
  std::string get_country_name() { return country_name; }
  Country GetCountryByName(std::string name);
};

#endif
