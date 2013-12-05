//
//  canvas.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-18.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__canvas__
#define __cs349_a1__canvas__

#include <iostream>
#include <vector>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>
#include <unistd.h>
#include "static.h"
#include "displayable.h"
#include "block.h"
#include "character.h"
#include "sun.h"
#include "enemy.h"
#include "canvasUnderlay.h"
#include "introText.h"
#include "constants.h"
#include "grid.h"
#include "xinfo.h"
#include <sstream>
#include <stdio.h>

class Canvas {
    std::vector <Displayable*> dlist;
    XInfo xInfo;
    Grid *g;
    void paintTerrainStripe(float x, int height);
public:
    Canvas(int argc, char*argv[], int width=WINDOW_DEFAULT_WIDTH, int height=WINDOW_DEFAULT_HEIGHT);
    ~Canvas();
    void initIntro();
    void initUnderlay();
    void initTerrain();
    Character* initCharacter();
    void initEnemies();
    void initFoods();
    void resetCharacter();
    Sun* initSun();
    
    void drawGrid();
    void paintAll();
    void repaint();
    Grid* getGrid() const;
    std::vector<Displayable*> getDlist() const;
    void eraseDlistElem(int i);
    unsigned long getColour(unsigned long colour) const;
    XInfo &getXInfo();
};

#endif /* defined(__cs349_a1__canvas__) */
