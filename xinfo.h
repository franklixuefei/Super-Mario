//
//  xinfo.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-20.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef cs349_a1_xinfo_h
#define cs349_a1_xinfo_h

struct XInfo {
    Window window;
    Display *display;
    int screen;
    GC gc;
    Pixmap pixmap; // for double buffering
    int width;
    int height;
    Pixmap tempPixmap; // for other purposes
    int tempWidth;
    int tempHeight;
    enum {White=0, Black, Red, Green, Blue, Cyan, Yellow, Magenta, Orange, Brown, Gray, LightSkyBlue, Gainsboro, DimGray, AntiqueWhite}; // Available colours.
    unsigned long colours[15];
};

#endif
