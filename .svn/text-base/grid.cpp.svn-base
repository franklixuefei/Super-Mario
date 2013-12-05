//
//  grid.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-19.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "grid.h"

Grid::Grid() {
    
    theGrid = new Cell*[MAX_ROWS];
    for (int i = 0; i < MAX_ROWS; ++i) {
        theGrid[i] = new Cell[MAX_COLUMNS];
    }
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            CCoords c;
            c.x = j*CELL_SIZE;
            c.y = i*CELL_SIZE;
            theGrid[i][j].setCoords(c);
        }
    }
}

Grid::~Grid() {
    for (int i = 0; i < MAX_ROWS; ++i) {
        delete [] theGrid[i];
    }
    delete [] theGrid;
}

Cell &Grid::getCell(int i, int j) {
    Cell & cell = theGrid[i][j];
    return cell;
}