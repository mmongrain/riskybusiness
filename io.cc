#include <iostream>
#include <fstream>
#include "io.h"
#include <string>
#include "map.h"

const int NUMBER_OF_CONTINENTS = 6;

// Saving method
static void save(int a, int b, std::string input) {
  std::ofstream output_filestream;
  output_filestream.open("World.map");
    
  std::string line;
  std::fstream myFile("World.map");
    
  std::string map [6][12];
    
  if(myFile.is_open()) {
    while (getline(myFile,line)) {
      for (int i=0; i<6; i++) {
        for (int j=0; j<12; j++) {
          map [i][j] = line;
        }
      }
    }
    
    map [a][b] = input;
    
    for (int i=0; i<6; i++) {
      for (int j=0; j<12; j++) {
        myFile << map [i][j] << std::endl;
      }
    }
  }
    
  output_filestream.close();
  std::cout << "The game has been saved successfully.";
}
    
// Loading method
static void load() {
  std::ifstream input_filestream;
  input_filestream.open("World.map");
    
  std::string line;
  std::ifstream myFile ("World.map");
    
  if (myFile.is_open()) {
    while (getline(myFile,line)) {
      std::cout << line << std::endl;
            
      // Splits each line into words(tokens)
      size_t position = 0;
      std::string delimiter = ",";
      std::string token;
      while ((position = line.find(delimiter))!=std::string::npos) {
        token = line.substr(0,position);
        line.erase(0,position+delimiter.length());
      }
    }
  }
  input_filestream.close();
    
  if(!myFile.is_open()) {
    std::cout << "An error ocurred. File not found." << std::endl;
  }
}
