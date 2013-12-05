//
//  block.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "block.h"

Block::Block(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas) : Displayable(drect, dtype, cells, canvas) {
    
}

Block::~Block() {}

void Block::paint(XInfo &xInfo) {
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::DimGray]);

#if !LOAD_IMAGE
#if DOUBLE_BUFFERING
    XFillRectangle(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), posAndSize.width, posAndSize.height);
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Gainsboro]);
    XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y)+posAndSize.height);
    XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y), (posAndSize.x+offset.x), (posAndSize.y+offset.y)+posAndSize.height);
#else
    XFillRectangle(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), posAndSize.width, posAndSize.height);
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Gainsboro]);
    XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y)+posAndSize.height);
    XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y), (posAndSize.x+offset.x), (posAndSize.y+offset.y)+posAndSize.height);
#endif
#else
    XImage *img;
    if (XpmCreateImageFromData (xInfo.display, ground_block_xpm, &img, NULL, NULL)) {
        printf ("Error reading file\n");
        exit (1);
    }
#if DOUBLE_BUFFERING
    XPutImage(xInfo.display, xInfo.pixmap, xInfo.gc, img, 0, 0, (posAndSize.x+offset.x), (posAndSize.y+offset.y), img->width, img->height );
#else
    XPutImage(xInfo.display, xInfo.window, xInfo.gc, img, 0, 0, (posAndSize.x+offset.x), (posAndSize.y+offset.y), img->width, img->height );
#endif
    
#endif
//    XFlush(xInfo.display);
    
}

#if XDEBUG
void Block::debug() {
    
}
#endif


void Block::loadBitmap(XInfo &xInfo) {
//    Pixmap bitmap;
//    
//    /* these variables will contain the dimensions of the loaded bitmap. */
//    unsigned int bitmap_width, bitmap_height;
//    
//    /* these variables will contain the location of the hot-spot of the   */
//    /* loaded bitmap.                                                    */
//    int hotspot_x, hotspot_y;
//    
//    /* this variable will contain the ID of the root window of the screen */
//    /* for which we want the pixmap to be created.                        */
//    Window root_win = DefaultRootWindow(xInfo.display);
//    
//    /* load the bitmap found in the file "icon.bmp", create a pixmap      */
//    /* containing its data in the server, and put its ID in the 'bitmap'  */
//    /* variable.                                                          */
//    int rc = XReadBitmapFile(xInfo.display, root_win,
//                             "ground_block.xbm",
//                             &bitmap_width, &bitmap_height,
//                             &bitmap,
//                             &hotspot_x, &hotspot_y);
//    /* check for failure or success. */
//    switch (rc) {
//        case BitmapOpenFailed:
//            fprintf(stderr, "XReadBitmapFile - could not open file 'icon.bmp'.\n");
//            break;
//        case BitmapFileInvalid:
//            fprintf(stderr,
//                    "XReadBitmapFile - file '%s' doesn't contain a valid bitmap.\n",
//                    "ground_block.xbm");
//            break;
//        case BitmapNoMemory:
//            fprintf(stderr, "XReadBitmapFile - not enough memory.\n");
//            break;
//        case BitmapSuccess:
//            /* bitmap loaded successfully - do something with it... */
//            xInfo.tempPixmap = bitmap;
//            xInfo.tempWidth = bitmap_width;
//            xInfo.tempHeight = bitmap_height;
//            break;
//    }
    
}

void Block::incrementInactivatedState() {
    inactivated = (inactivated + 1) % BLOCK_INACTIVATED_COUNTER;
}