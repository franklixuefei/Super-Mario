//
//  displayable.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__displayable__
#define __cs349_a1__displayable__

#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "constants.h"
#include <vector>
#include "cell.h"
#include "xinfo.h"
#include "utils.h"
#include <cstdio>

class Canvas;
struct DRect { // 1.0 is defined as the 1/CELL_SIZE of width/height of a cell
    int x; // x-coord of upper left corner
    int y; // y-coord of upper left corner
    int width; // width of the displayable
    int height; // height of the displayable
    DRect();
};

struct DOffset {
    int x;
    int y;
};

enum DType {
    BLOCK,
    FOOD,
    ENEMY,
    MARIO,
    SUN,
    UNDERLAY,
    INTROTEXT,
    UNKNOWN
};



class Displayable {
    std::vector<Cell*> cells; // cells involved
protected:
    DRect posAndSize;
    DType type;
    Canvas *canvas;
    DRect posAndSizeBeforeJumping;
    std::vector<Cell*>  calculateInvolvedCells();
    void updateInvolvedCells(std::vector<Cell*>involvedCells);
    void setCellsSolid(bool solid);
    DOffset offset;
    int inactivated;
    bool needsPaint;
public:
    Displayable(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    virtual ~Displayable()=0;
    virtual void paint(XInfo &xInfo)=0;
    bool moveBy(int x, int y, bool shouldSolidifyCells=true);
    bool move(int x, int y, bool shouldSolidifyCells=true);
    bool jumpTrajectory(int x, int y); // move relative to initial position
    Cell* collisionDetection();
    virtual void loadBitmap(XInfo &xInfo)=0;
    void solidifyOccupiedCells();
    DType getType() const;
    void setPosAndSizeBeforeJumping();
    
    int getInactivatedState(); // 0 means activated
    virtual void incrementInactivatedState()=0;
    void updateOffset(int x, int y);
    
    bool getNeedsPaint() const;
    void setNeedsPaint(bool paint);
#if XDEBUG
    virtual void debug();
#endif

};

#endif /* defined(__cs349_a1__displayable__) */
