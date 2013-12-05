//
//  introText.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-29.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__introText__
#define __cs349_a1__introText__

#include <iostream>
#include "displayable.h"
#include "constants.h"
#include "static.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>

class IntroText : public Displayable {
public:
    IntroText(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas *canvas);
    ~IntroText();
    void paint(XInfo &xInfo);
    void loadBitmap(XInfo &xInfo);
#if XDEBUG
    void debug();
#endif
    void incrementInactivatedState();
};

#endif /* defined(__cs349_a1__introText__) */
