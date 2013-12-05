//
//  sun.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "sun.h"


Sun::Sun(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas) : Displayable(drect, dtype, cells, canvas) {}

Sun::~Sun() {}

void Sun::paint(XInfo &xInfo) {
#if LOAD_IMAGE
    XImage *img;
    XSetBackground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::White]);
    if (XpmCreateImageFromData (xInfo.display, sun_xpm, &img, NULL, NULL)) {
        printf ("Error reading file\n");
        exit (1);
    }
    XPutImage(xInfo.display, xInfo.window, xInfo.gc, img, 0, 0, (posAndSize.x+offset.x), (posAndSize.y+offset.y), img->width, img->height );
#else
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Yellow]);
#if DOUBLE_BUFFERING
    XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), posAndSize.width, posAndSize.height, 0, 360*64);
#else
    XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), posAndSize.width, posAndSize.height, 0, 360*64);
#endif
#endif
}

bool Sun::outOfWindow() {
    return posAndSize.x > WINDOW_DEFAULT_WIDTH;
}

#if XDEBUG
void Sun::debug() {
    
}
#endif

void Sun::loadBitmap(XInfo &xInfo) {
    
}


void Sun::incrementInactivatedState() {
    inactivated = (inactivated + 1) % SUN_INACTIVATED_COUNTER;
}
