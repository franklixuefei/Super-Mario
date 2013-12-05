//
//  cell.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-19.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__cell__
#define __cs349_a1__cell__

#include <iostream>
#include "constants.h"
#include <stdio.h>

struct CCoords { // unit is pixel
    int x;
    int y;
};

struct RelCoords { // unit is (CELL_SIZE pixels)
    int x;
    int y;
};

class Displayable;

class Cell {
    CCoords cellPos;
    bool solid;
    int dtype;
    Displayable *d; // the Displayable this cell belongs to.
public:
    Cell();
    ~Cell();
    bool isSolid();
    void setSolid(bool solid, int type);
    int getDType() const;
    CCoords getCoords() const;
    void setCoords(CCoords ccoords);
    void setDisplayable(Displayable *displayable);
    Displayable* getDisplayable() const;
};


#endif /* defined(__cs349_a1__cell__) */
