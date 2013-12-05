//
//  enemy.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-25.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "enemy.h"

Enemy::Enemy(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas) : Displayable(drect, dtype, cells, canvas) {}

Enemy::~Enemy() {}


void Enemy::paint(XInfo &xInfo) {
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[XInfo::Red]);
#if DOUBLE_BUFFERING
    XFillArc(xInfo.display, xInfo.pixmap, xInfo.gc, posAndSize.x+offset.x, posAndSize.y+offset.y, posAndSize.width, posAndSize.height, 0, 360*64);
#else
    XFillArc(xInfo.display, xInfo.window, xInfo.gc, posAndSize.x+offset.x, posAndSize.y+offset.y, posAndSize.width, posAndSize.height, 0, 360*64);
#endif
}

void Enemy::loadBitmap(XInfo &xInfo) {
    
}

#if XDEBUG
void Enemy::debug() {
    
}
#endif

void Enemy::incrementInactivatedState() {
}