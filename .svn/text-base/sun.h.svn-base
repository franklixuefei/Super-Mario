//
//  sun.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__sun__
#define __cs349_a1__sun__

#include <iostream>
#include "displayable.h"
#include <cstdio>

class Canvas;
class Sun : public Displayable {
public:
    Sun(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas* canvas);
    ~Sun();
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
    bool outOfWindow();
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__sun__) */
