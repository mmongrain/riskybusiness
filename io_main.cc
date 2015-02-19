//
//  main.cpp
//  Driver
//
//  Created by Leonard Nguyen on 2015-01-26.
//  Copyright (c) 2015 Leonard Nguyen. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "IORisk.cpp"
#include "IORisk.h"
#include "Map.h"
#include <string>


int main(int argc, const char * argv[]) {
    
    int answer;
    int i,j,k;
    std::string input;
    
    std::cout << "Enter 1 to load or 2 to save" << std::endl;
    std::cin >> answer;
    
    if(answer==1)
        load();
    else if(answer==2) {
        std::cout << "Which data would you like to modify? Enter the index of continent and the country." << std::endl;
        std::cin >> i;
        std::cin >> j;
        std::cout << "What is your input?" << std::endl;
        std::cin >> input;
        save(i,j, input);
    }
    else
        std::cout << "Invalid value entered.";
    
    
    
    return 0;
}


