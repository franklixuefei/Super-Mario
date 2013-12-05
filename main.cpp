//
//  main.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//
#include "mario.h"
#include "constants.h"
#include <iostream>
#include <cstdlib>

int main(int argc, char * argv[])
{
    Mario mario(argc, argv);
    mario.start();
#if XDEBUG
    std::cerr<<"Destructor executed."<<std::endl;
#endif
    return 0;
}

