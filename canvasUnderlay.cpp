//
//  canvasUnderlay.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-29.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "canvasUnderlay.h"

CanvasUnderlay::CanvasUnderlay(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas) : Displayable(drect, dtype, cells, canvas) {}

CanvasUnderlay::~CanvasUnderlay() {}


void CanvasUnderlay::paint(XInfo &xInfo) {
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::LightSkyBlue]);
#if DOUBLE_BUFFERING
    XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc, posAndSize.x+offset.x, posAndSize.y+offset.y, posAndSize.width, posAndSize.height);
#else
    XFillRectangle(xInfo.display, xInfo.window, xInfo.gc, posAndSize.x+offset.x, posAndSize.y+offset.y, posAndSize.width, posAndSize.height);
#endif
}

void CanvasUnderlay::loadBitmap(XInfo &xInfo) {
    
}

#if XDEBUG
void CanvasUnderlay::debug() {
    
}
#endif

void CanvasUnderlay::incrementInactivatedState() {
    
}
