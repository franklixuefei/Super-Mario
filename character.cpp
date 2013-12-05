//
//  character.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "character.h"

Character::Character(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas* canvas) : Displayable(drect, dtype, cells, canvas), direction(true), state(STANDING), velosity(std::make_pair(MARIO_HORIZONTAL_SPEED, MARIO_VERTICAL_SPEED)) {}

Character::~Character() {}

void Character::setDirection(bool dir) {
    if (this->direction != dir) this->direction = dir;
}

bool Character::getDirection() const {
    return direction;
}

void Character::setState(Character::State s) {
    if (state != s) state = s;
}

Character::State Character::getState() const {
    return state;
}

void Character::paint(XInfo &xInfo) {
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
#if XDEBUG
    XDrawRectangle(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y), posAndSize.width, posAndSize.height);
#endif

    double scale = CELL_SIZE / 50; // for scaling Mario if cell size changed.
    if (direction) {
#if DOUBLE_BUFFERING
        // draw head
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::AntiqueWhite]);
        XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 0, 360*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Red]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 25, (180-25)*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+10+posAndSize.width/2-posAndSize.width/2*cos(PI/6)-2, (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6), (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6));
        XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+16, 4, 4, 0, 360*64);
        // draw body
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30);
        // draw shoulder
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42);
#else
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::AntiqueWhite]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 0, 360*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Red]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 12, (180-12)*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10+posAndSize.width/2-posAndSize.width/2*cos(PI/6)-2, (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6), (posAndSize.x+offset.x)+posAndSize.width, (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6));
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+16, 4, 4, 0, 360*64);
        // draw body
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30);
        // draw shoulder
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42);
#endif
        switch (state) {
            case RUNNING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+44, (posAndSize.y+offset.y)+58);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left hand
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+22, (posAndSize.y+offset.y)+60);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+40, (posAndSize.y+offset.y)+74);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+40, (posAndSize.y+offset.y)+74, (posAndSize.x+offset.x)+44, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x), (posAndSize.y+offset.y)+94);
                
                break;
#else
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+44, (posAndSize.y+offset.y)+58);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left hand
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+22, (posAndSize.y+offset.y)+60);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+40, (posAndSize.y+offset.y)+74);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+40, (posAndSize.y+offset.y)+74, (posAndSize.x+offset.x)+44, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x), (posAndSize.y+offset.y)+94);
                
                break;

#endif
            case STANDING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+64);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+64);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#else
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+64);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+64);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#endif
            case JUMPING:case FALLING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+42, (posAndSize.y+offset.y)+24);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+8, (posAndSize.y+offset.y)+24);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#else
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+42, (posAndSize.y+offset.y)+24);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+8, (posAndSize.y+offset.y)+24);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#endif
            default:
                ;
                
        }
    } else {
        // draw head
#if DOUBLE_BUFFERING
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::AntiqueWhite]);
        XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 0, 360*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Red]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 25, (180-25)*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6), (posAndSize.x+offset.x)+10+posAndSize.width/2-posAndSize.width/2*cos(PI/6)+2*15*cos(PI/6), (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6));
        XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+16, 4, 4, 0, 360*64);
        // draw body
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30);
        // draw shoulder
        XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42);
#else
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::AntiqueWhite]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 0, 360*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Red]);
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y), posAndSize.width-20, posAndSize.height/2-20, 12, (180-12)*64);
        XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Black]);
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x), (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6), (posAndSize.x+offset.x)+10+posAndSize.width/2-posAndSize.width/2*cos(PI/6)+2*15*cos(PI/6), (posAndSize.y+offset.y)+posAndSize.width/2-posAndSize.width/2*sin(PI/6));
        XFillArc(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+16, 4, 4, 0, 360*64);
        // draw body
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30);
        // draw shoulder
        XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42);
#endif
        switch (state) {
            case RUNNING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+28, (posAndSize.y+offset.y)+60);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+6, (posAndSize.y+offset.y)+58);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+6, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+74);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+74, (posAndSize.x+offset.x)+50, (posAndSize.y+offset.y)+94);
                
                break;
#else
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+28, (posAndSize.y+offset.y)+60);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+6, (posAndSize.y+offset.y)+58);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+10, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+6, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+74);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+74, (posAndSize.x+offset.x)+50, (posAndSize.y+offset.y)+94);
                
                break;
#endif
            case STANDING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+64);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+64);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#else
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53);
                // draw right lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+34, (posAndSize.y+offset.y)+64);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53);
                // draw left lower arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+53, (posAndSize.x+offset.x)+16, (posAndSize.y+offset.y)+64);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#endif
            case JUMPING:case FALLING:
#if DOUBLE_BUFFERING
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+42, (posAndSize.y+offset.y)+24);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+8, (posAndSize.y+offset.y)+24);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.pixmap, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#else
                // draw right upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+30, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+42, (posAndSize.y+offset.y)+24);
                // draw left upper arm
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+20, (posAndSize.y+offset.y)+42, (posAndSize.x+offset.x)+8, (posAndSize.y+offset.y)+24);
                // draw right upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78);
                // draw right lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+32, (posAndSize.y+offset.y)+100);
                // draw left upper leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+25, (posAndSize.y+offset.y)+30+30, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78);
                // draw left lower leg
                XDrawLine(xInfo.display, xInfo.window, xInfo.gc, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+78, (posAndSize.x+offset.x)+18, (posAndSize.y+offset.y)+100);
                
                break;
#endif
            default:
                ;
                
        }
    }
//    XFlush(xInfo.display);
    
    }

int Character::jump(double initial_time, double vx, double vy, double scale) {
    float timeInterval = (Utils::now() - initial_time)/1000000;
    int yDisplacement = (vy/sqrt(JUMP_SPEED)*sqrt(scale))*timeInterval - 0.5*(980/JUMP_SPEED*scale)*timeInterval*timeInterval;
    int xDisplacement = (vx/sqrt(JUMP_SPEED)*sqrt(scale))*timeInterval;
#if XDEBUG
    fprintf(stderr, "time interval: %f, X displacement: %d, Y displacement: %d\n", timeInterval, xDisplacement, yDisplacement);
#endif
    return this->jumpTrajectory(xDisplacement, -yDisplacement) ? 0 : 1;
}


#if XDEBUG
void Character::debug() {
    
}
#endif

void Character::loadBitmap(XInfo &xInfo) {
    
}

void Character::setVelosity(double vx, double vy) {
    velosity.first = vx;
    velosity.second = vy;
}

std::pair<double, double>Character::getVelosity() const {
    return this->velosity;
}

void Character::incrementInactivatedState() {
    inactivated = (inactivated + 1) % CHARACTER_INACTIVATED_COUNTER;
}
