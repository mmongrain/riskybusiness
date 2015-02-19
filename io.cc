//
//  IORisk.cpp
//  Driver
//
//  Created by Leonard Nguyen on 2015-01-26.
//  Copyright (c) 2015 Leonard Nguyen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "IORisk.h"
#include <string>
#include "Map.h"



const int NUMBER_OF_CONTINENTS = 6;

// Saving method
static void save(int a, int b, std::string input) {
    std::ofstream outputfilestream;
    outputfilestream.open("World.map");
    
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
    
    outputfilestream.close();
    std::cout << "The game has been saved successfully.";
    
}

    
    
// Loading method
static void load() {
    std::ifstream inputFilestream;
    inputFilestream.open("World.map");
    
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
                
                //std::string*** map = new std::string**[6];
                
                // Dynamic Multidimensional Array (3 Dimensions)
                /* 6 continents
                for (int i=0; i<6; i++) {
                    *map[i] = new std::string[12];
                    // From 4-12 countries per continent
                    for (int j=0; j<12; j++) {
                        map [i][j] = new std::string[10];
                        // From 6-10 data for each country
                        for (int k=0; k<10; k++) {
                            map [i][j][k] = token;
                        }
                    }
                }*/
                line.erase(0,position+delimiter.length());
            }
            
        }
    }
    inputFilestream.close();
    
    if(!myFile.is_open()) {
        std::cout << "An error ocurred. File not found." << std::endl;
    }
}