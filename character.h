//
//  character.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__character__
#define __cs349_a1__character__

#include <iostream>
#include "displayable.h"
#include <cmath>
#include <vector>
#include <cstdio>

class Canvas;
class Character : public Displayable {
public:
    enum State {
        RUNNING,
        STANDING,
        JUMPING,
        FALLING
    };
private:
    bool direction; // true for right, false for left.
    State state;
    std::pair<double, double> velosity;
public:
    Character(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    ~Character();
    void setDirection(bool dir);
    bool getDirection() const;
    void setState(State s);
    State getState() const;
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
    int jump(double initial_time, double vx, double vy, double scale);
    void setVelosity(double vx, double vy);
    std::pair<double, double>getVelosity() const;
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__character__) */
