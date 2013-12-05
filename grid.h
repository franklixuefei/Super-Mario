//
//  grid.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-19.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__grid__
#define __cs349_a1__grid__

#include <iostream>
#include "cell.h"
#include "constants.h"
#include <stdio.h>

class Grid {
    Cell **theGrid;
public:
    Grid();
    ~Grid();
    Cell &getCell(int i, int j);

};

#endif /* defined(__cs349_a1__grid__) */
