//
//  mario.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__mario__
#define __cs349_a1__mario__

#include <iostream>
#include "canvas.h"
#include "eventListener.h"
#include <stdio.h>
#include <cmath>

class Mario {
    Canvas *canvas;
    EventListener *eventListener;
public:
    Mario(int argc, char* argv[]);
    void start();
    ~Mario();
};

#endif /* defined(__cs349_a1__mario__) */
