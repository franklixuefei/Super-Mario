//
//  cell.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-19.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "cell.h"
#include "displayable.h"

Cell::Cell() : cellPos(CCoords()), solid(false), dtype(UNKNOWN), d(NULL) {}

Cell::~Cell() {}

bool Cell::isSolid() {
    return solid;
}

void Cell::setSolid(bool solid, int type) {
    this->solid = solid;
    if (solid) {
        this->dtype = type;
    } else {
        this->dtype = UNKNOWN;
    }
#if XDEBUG
    std::cerr << "Cell " << (this->solid ? "solid" : "NOT solid") << " at coords: X: " << cellPos.x << " Y: " << cellPos.y << std::endl;
#endif
}

CCoords Cell::getCoords() const{
    return cellPos;
}

void Cell::setCoords(CCoords ccoords) {
    cellPos.x = ccoords.x;
    cellPos.y = ccoords.y;
}

int Cell::getDType() const {
    return dtype;
}

void Cell::setDisplayable(Displayable *displayable) {
    this->d = displayable;
}

Displayable* Cell::getDisplayable() const {
    return this->d;
}