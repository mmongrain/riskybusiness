//
//  IORisk.h
//  Driver
//
//  Created by Leonard Nguyen on 2015-01-26.
//  Copyright (c) 2015 Leonard Nguyen. All rights reserved.
//

#ifndef __Driver__IORisk__
#define __Driver__IORisk__

#include <stdio.h>
#include <string>string


class IORisk{
    
private:
    const int NUMBER_OF_CONTINENTS;
    const int NUMBER_OF_TERRITORIES;
    
public:
    void save();
    void load();
    
};



#endif /* defined(__Driver__IORisk__) */
