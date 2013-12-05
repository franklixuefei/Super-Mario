//
//  eventListener.h
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#ifndef __cs349_a1__eventListener__
#define __cs349_a1__eventListener__

#include <iostream>
#include "canvas.h"
#include "constants.h"
#include <vector>
#include <stdio.h>

class EventListener {
    Canvas *canvas;
    std::vector<Displayable*> controllees;
    bool __stopSignal;
    XEvent event;
    XEvent prevEvent;
    KeySym key;
    KeySym prevKey;
    int inControlles(Displayable* d);
    
    unsigned int fps;
    unsigned int sunSpeed;
    unsigned int runSpeed;
    unsigned int jumpSpeed;
    
    void handleResize();
    void handleKeyPress();
    void handleKeyRelease();
    
    void handleJump();
    
    void handleAnimation();
    
    void introKeyPress();
    
    void introKeyRelease();
    
    unsigned long __lastTime;
    
    bool __keyHeldDown; // deprecated
    int __motionMask; // 1: left; 10: right; 100: j; 1000: free-fall;
    unsigned long __timeWhenMovementBegan; // reset to 0 after jumping
    std::pair<double, double>velosityScale; // vx and vy
    
    void lookupKeySymbol();
public:
    EventListener(Canvas *canvas, unsigned int fps, unsigned int runSpeed, unsigned int sunSpeed, unsigned int jumpSpeed);
    ~EventListener();
    void registerDisplayable(Displayable *d);
    void unregisterDisplayable(Displayable *d);
    void start();
    void stop();

};


#endif /* defined(__cs349_a1__eventListener__) */
