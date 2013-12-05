//
//  introText.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-29.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "introText.h"

IntroText::IntroText(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas) : Displayable(drect, dtype, cells, canvas) {}

IntroText::~IntroText() {}


void IntroText::paint(XInfo &xInfo) {
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
    const char * s = "~Press space to get started!~";
    int str_len = (int)strlen(s);
    
#if DOUBLE_BUFFERING
    XDrawImageString(xInfo.display, xInfo.pixmap, xInfo.gc, posAndSize.x+offset.x, posAndSize.y+offset.y, s, strlen(s));
#else
    XDrawImageString(xInfo.display, xInfo.window, xInfo.gc, posAndSize.x+offset.x+(WINDOW_DEFAULT_WIDTH-str_len)/2, posAndSize.y+offset.y+100, s, str_len);
#endif
}

void IntroText::loadBitmap(XInfo &xInfo) {

}

#if XDEBUG
void IntroText::debug() {
    
}
#endif

void IntroText::incrementInactivatedState() {
    
}
