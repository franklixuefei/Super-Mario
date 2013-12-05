//
//  block.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__block__
#define __cs349_a1__block__

#include <iostream>
#include "displayable.h"
#include "constants.h"
#include "static.h"
#include <cstdio>

class Canvas;

class Block : public Displayable {
public:
    Block(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    ~Block();
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__block__) */
