//
//  Map.cpp
//  Driver
//
//  Created by Leonard Nguyen on 2015-02-05.
//  Copyright (c) 2015 Leonard Nguyen. All rights reserved.
//

#include "Map.h"
#include "Country.h"
#include <string>
#include <iostream>

Map::Map() {
    Country::Country countries [6][15];
    
    std::string** map = new std::string*[6];
    
    for (int i=0; i<6; i++) {
        map[i] = new std::string[15];
        for (int j=0; j<15; j++) {
            //map [i][j]= The data coming from somewhere
            
        }
    }
}