//
//  enemy.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-25.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__enemy__
#define __cs349_a1__enemy__

#include <iostream>
#include "displayable.h"

class Enemy : public Displayable {
public:
    Enemy(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    ~Enemy();
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__enemy__) */
