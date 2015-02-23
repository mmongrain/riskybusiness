#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

class Map { 

  private:

    struct MapInfo {
      std::string author;
      std::string image;
      bool wrap;
      char scroll;
      bool warn;
    } map_info;

  public:

    struct Territory {
      friend class Map;
      private:
        std::string name;
        int x;
        int y;
        std::string continent;
        std::vector<std::string> adjacency_list;
      public:
        std::string get_name() { return name; }
        int get_x() { return x; }
        int get_y() { return y; }
        std::string get_continent() { return continent; }
        std::vector<std::string> get_adjacency_list() { return adjacency_list; }
        std::string ToString();
    };
  
    struct Continent {
      friend class Map;
      private:
        std::string name;
        int victory_size;
        std::vector<Territory> territories;
      public:
        std::string get_name() { return name; }
        int get_victory_size() { return victory_size; }
        std::vector<Territory> get_territories() { return territories; }
    };

  private:

    std::vector<Continent> continents;
    std::vector<Territory> territories;

    void LoadMap(char* filename);
    void ParseMapInfo(const std::vector<std::string> &section_map);
    void ParseContinentInfo(const std::vector<std::string> &section_continents);
    void ParseTerritoryInfo(const std::vector<std::string> &section_continents);

  public:

    Map();
    Map(char* filename);

    std::string get_author() { return map_info.author; }
    std::string get_image()  { return map_info.image; }
    bool get_wrap()          { return map_info.wrap; }
    char get_scroll()        { return map_info.scroll; }
    bool get_warn()          { return map_info.warn; }

    std::vector<Continent> get_continents()  { return continents; }
    std::vector<Territory> get_territories() { return territories; }
};

int main () {
  char filename[100] = "World (small).map";
  Map map(filename);
  std::cout << "author: " << map.get_author() 
            << ", image: " << map.get_image()
            << ", wrap: " << map.get_wrap() 
            << ", scroll: " << map.get_scroll()
            << ", warn: " << map.get_warn() << std::endl; 
  std::vector<Map::Continent> continents = map.get_continents();
  std::vector<Map::Territory> territories = map.get_territories();
  for (int i = 0; i < continents.size(); i++) {
    std::cout << "name: " << continents[i].get_name()
              << ", victory_size: " << continents[i].get_victory_size() << std::endl;
  }
  for (int i =0; i < territories.size(); i++) {
    std::cout << territories[i].ToString() << std::endl;
  }
  return 0;
}

std::string Map::Territory::ToString() {
  std::string out = "name:" + name + ", x:" + std::to_string(x) + ", y:" + 
                    std::to_string(y) + ", continent:" + continent + 
                    ", adjacency list:";
  for (int i = 0; i < adjacency_list.size(); i ++) {
    out = out + adjacency_list[i] + ", ";
  }
  return out;
}

Map::Map() {}

Map::Map(char* filename) {
  LoadMap(filename);
}

void Map::LoadMap(char* filename) {
  std::ifstream file(filename);
  std::vector<std::string> section_map;
  std::vector<std::string> section_continents;
  std::vector<std::string> section_territories;
  std::string input;

  // Eat any blank lines before [Map], ensure [Map] exists, eat [Map]:
  while (getline(file, input) && input.find("[Map]") == std::string::npos);

  // Read the contents of [Map] to a vector, eat [Continents] 
  while (getline(file, input) && input.find("[Continents]") == std::string::npos) {
    if (input.length() >= 3) { // Minimum protection against incorrect formatting
      section_map.push_back(input);
    } 
  }

  // Read the contents of [Continents] to a vector, eat [Territories];
  while (getline(file, input) && input.find("[Territories]") == std::string::npos) {
    if (input.length() >= 3) {
      section_continents.push_back(input);
    }
  }

  // Read the contents of [Territories] to a vector:
  while (getline(file, input)) {
    if (input.length() >= 9) { // Shortest correctly-formated line is N,x,y,C,A
      section_territories.push_back(input);
    }
  }

  ParseMapInfo(section_map);
  ParseContinentInfo(section_continents);
  ParseTerritoryInfo(section_territories);
} 

void Map::ParseMapInfo(const std::vector<std::string> &section_map) {
  for (int i = 0; i < section_map.size(); i++) {
    std::size_t delim = section_map[i].find("=");
    /**
     * WARNING: Possible portability problem 
     * For some reason each line on my system is followed by two invisible
     * characters that badly bork the strings. (This might be a feature of
     * Windows-formatted files). -2 is a magic number, and may be different on 
     * your system. 
     * TODO: Find out what's actually going on
     */
    int end_of_string = section_map[i].length() - delim - 2;
    std::string field = section_map[i].substr(0, delim);
    std::string value = section_map[i].substr(delim + 1, end_of_string); 
    // std::cout << i << ". field: " << field << ", value: " << value << std::endl;

    // Can't use switch because std::string isn't a primitive. Bummer
    // Convert field to an enum when you get the chance
    if (field.compare("author") == 0) { // "If strings are identical" 
      map_info.author = value;

    } else if (field.compare("image") == 0) {
      map_info.image = value;

    } else if (field.compare("wrap") == 0) {
      map_info.wrap = (value.compare("yes") == 0);
    
    } else if (field.compare("scroll") == 0) {
      if (value.compare("horizontal") == 0) {
        map_info.scroll = 'h';
      } else if (value.compare("vertical") == 0) {
        map_info.scroll = 'v';
      } else {
        map_info.scroll = 'n';
      }

    } else if (field.compare("warn") == 0) {
      map_info.warn = (value.compare("yes") == 0);
    }
  }
}

void Map::ParseContinentInfo(const std::vector<std::string> &section_continents) {
  for (int i = 0; i < section_continents.size(); i++) {
    std::size_t delim = section_continents[i].find("=");
    Continent continent;
    continent.name = section_continents[i].substr(0, delim);
    // stoi is available in c++11, make sure your compiler supports, it converts int to str
    // compilation flag is -std=c++11
    continent.victory_size = std::stoi(section_continents[i].substr(delim + 1));
    continents.push_back(continent);
  }
}

void Map::ParseTerritoryInfo(const std::vector<std::string> &section_territories) {
  for (int i = 0; i < section_territories.size(); i++) {
    Territory temp;
    std::vector<std::string> territory;
    std::stringstream input(section_territories[i]);
    std::string token;
    while (getline(input, token, ',')) {
      token = token.substr(0, token.length());
      territory.push_back(token);
    }

    // Eats the EOF character, which breaks everything
    int last = territory.size() - 1;
    territory[last] = territory[last].substr(0, territory[last].length() - 1);

    // Write to the territory struct and add it to the master territories list
    temp.name = territory[0];
    temp.x = std::stoi(territory[1]);
    temp.y = std::stoi(territory[2]);
    temp.continent = territory[3];
    for (int i = 4; i < territory.size(); i++) {
      temp.adjacency_list.push_back(territory[i]);
    }
    territories.push_back(temp);
  }
}

    
