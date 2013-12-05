//
//  canvasUnderlay.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-29.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__canvasUnderlay__
#define __cs349_a1__canvasUnderlay__

#include <iostream>
#include "displayable.h"
#include "constants.h"
#include "static.h"
#include <stdio.h>

class CanvasUnderlay : public Displayable {
public:
    CanvasUnderlay(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    ~CanvasUnderlay();
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__canvasUnderlay__) */
