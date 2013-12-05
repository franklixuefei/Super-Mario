//
//  eventListener.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "eventListener.h"

EventListener::EventListener(Canvas *canvas, unsigned int fps, unsigned int runSpeed, unsigned int sunSpeed, unsigned int jumpSpeed) : canvas(canvas), fps(fps), sunSpeed(sunSpeed), runSpeed(runSpeed), jumpSpeed(jumpSpeed), __lastTime(Utils::now()), __keyHeldDown(false), __motionMask(0), __timeWhenMovementBegan(0),  velosityScale(std::make_pair(1, 1)){}

EventListener::~EventListener() {
    controllees.clear();
}

int EventListener::inControlles(Displayable *d) {
    for (int i = 0; i < controllees.size(); ++i) {
        if (d == controllees[i]) return i;
    }
    return -1;
}


// update width and height when window is resized
void EventListener::handleResize() {
    XInfo &xInfo = canvas->getXInfo();
	XConfigureEvent xce = event.xconfigure;
	fprintf(stderr, "Handling resize  w=%d  h=%d\n", xce.width, xce.height);
	if (xce.width != xInfo.width || xce.height != xInfo.height) {
#if DOUBLE_BUFFERING
        XFreePixmap(xInfo.display, xInfo.pixmap);
		int depth = DefaultDepth(xInfo.display, DefaultScreen(xInfo.display));
		xInfo.pixmap = XCreatePixmap(xInfo.display, xInfo.window, xce.width, xce.height, depth);
#endif
        std::vector<Displayable*> dlist = canvas->getDlist();
        for (int i = 0; i < dlist.size(); ++i) {
            dlist[i]->updateOffset((xce.width - WINDOW_DEFAULT_WIDTH)/2, (xce.height - WINDOW_DEFAULT_HEIGHT)/2);
        }
		xInfo.width = xce.width;
		xInfo.height = xce.height;
	}
    
}

void EventListener::handleKeyPress() {
    prevKey = key;
	lookupKeySymbol();
    switch (key) {
        case JUMP_KEY:
#if XDEBUG
            printf("jumping!");
#endif
            if (!(__motionMask & BIT_MASK_FREE_FALLING)) {
                __motionMask |= BIT_MASK_JUMPING;
                if ( (__motionMask & BIT_MASK_LEFT_MOVING) || (__motionMask & BIT_MASK_RIGHT_MOVING) ) {
                    __motionMask &= ~BIT_MASK_LEFT_MOVING;
                    __motionMask &= ~BIT_MASK_RIGHT_MOVING;
                    velosityScale.first = 3;
                    velosityScale.second = 1.2;
                }
            }
            break;
        case Q_KEY: case EXC_KEY:
            std::cerr << "Game terminated" << std::endl;
			stop();
            break;
        case LEFT_ARROW:
            for (int i = 0; i < controllees.size(); ++i) {
                Displayable *d = controllees[i];
                if (d->getType() == MARIO) {
                    
                    ((Character*)d)->setDirection(false); // only change direction if jumping
                    if (!(__motionMask & BIT_MASK_JUMPING) && !(__motionMask & BIT_MASK_FREE_FALLING)) {
                        __motionMask |= BIT_MASK_LEFT_MOVING;
                        ((Character*)d)->setState(Character::RUNNING);
                        double vx = ((Character*)d)->getVelosity().first;
                        double vy = ((Character*)d)->getVelosity().second;
                        ((Character*)d)->setVelosity(vx<0?vx:-vx, vy);
                    } else {
                        event = prevEvent; // restore event from left-key pressing to j key pressing for example
                    }
                }
            }
            break;
        case RIGHT_ARROW:
            for (int i = 0; i < controllees.size(); ++i) {
                Displayable *d = controllees[i];
                if (d->getType() == MARIO) {
                    ((Character*)d)->setDirection(true);
                    if ( !(__motionMask & BIT_MASK_JUMPING) && !(__motionMask & BIT_MASK_FREE_FALLING) ) {
                        __motionMask |= BIT_MASK_RIGHT_MOVING;
                        ((Character*)d)->setState(Character::RUNNING);
                        double vx = ((Character*)d)->getVelosity().first;
                        double vy = ((Character*)d)->getVelosity().second;
                        ((Character*)d)->setVelosity(vx>0?vx:-vx, vy);
                    } else {
                        event = prevEvent;
                    }
                }
            }
            break;
        default:

            event = prevEvent; // if other keys are pressed, just restore the "other key" event to previous "right" event.
#if XDEBUG
            fprintf(stderr, "event type: %d\n", event.type);
#endif
            break;
    }

}

void EventListener::handleKeyRelease() {
    prevKey = key;
	lookupKeySymbol();
    switch (key) {
        case JUMP_KEY:
            break;
        case Q_KEY: case EXC_KEY:
            
            break;
        case LEFT_ARROW:
            for (int i = 0; i < controllees.size(); ++i) {
                Displayable *d = controllees[i];
                if (d->getType() == MARIO) {
                    __motionMask &= ~BIT_MASK_LEFT_MOVING;
                    if ( !(__motionMask & BIT_MASK_JUMPING) ) {
                        ((Character*)d)->setState(Character::STANDING);
                    } else {
                        event = prevEvent;
                    }
                }
            }
            break;
        case RIGHT_ARROW:
            for (int i = 0; i < controllees.size(); ++i) {
                Displayable *d = controllees[i];
                if (d->getType() == MARIO) {
                    __motionMask &= ~BIT_MASK_RIGHT_MOVING;
                    if ( !(__motionMask & BIT_MASK_JUMPING) ) {
                        ((Character*)d)->setState(Character::STANDING);
                    } else {
                        event = prevEvent;
                    }
                }
            }
            break;
        default:
            event = prevEvent;
            break;
    }
}

void EventListener::handleJump() {
    for (int i = 0; i < controllees.size(); ++i) {
        Displayable *d = controllees[i];
        if (d->getType() == MARIO) {
            if (!__timeWhenMovementBegan) {
                __timeWhenMovementBegan = Utils::now();
                ((Character*)d)->setPosAndSizeBeforeJumping();
            }
            if (((Character*)d)->getState() != Character::JUMPING) {
                ((Character*)d)->setState(Character::JUMPING);
                __motionMask |= BIT_MASK_JUMPING;
                
            }
            int ret = ((Character*)d)->jump(__timeWhenMovementBegan, ((Character*)d)->getVelosity().first * velosityScale.first, ((Character*)d)->getVelosity().second * velosityScale.second, jumpSpeed); // check whether d is still jumping
            if (ret) { // if not, stop.
                __motionMask &= ~BIT_MASK_JUMPING;
                __timeWhenMovementBegan = 0;
                velosityScale.first = velosityScale.second = 1;
                ((Character*)d)->setState(Character::STANDING);
                double vx = ((Character*)d)->getVelosity().first;
                double vy = ((Character*)d)->getVelosity().second;
                bool dir = ((Character*)d)->getDirection();
                ((Character*)d)->setVelosity((dir?vx>0:vx<0)?vx:-vx, vy);
            }
        }
    }
}

void EventListener::handleAnimation() {
    // Animate the Sun
    for (int i = 0; i < controllees.size(); ++i) {
        Displayable *d = controllees[i];
        if (d->getType() == SUN) {
            if (sunSpeed < 5) {
                ((Sun*)d)->incrementInactivatedState();
                if ( ((Sun*)d)->getInactivatedState() == 0 ) {
                    ((Sun*)d)->moveBy((int)(Utils::now()-__lastTime)/10000*sunSpeed, 0, false);
                }
            } else {
                ((Sun*)d)->moveBy((int)(Utils::now()-__lastTime)/10000*(sunSpeed-4), 0, false);
            }
            if ( ((Sun*)d)->outOfWindow() ) {
                ((Sun*)d)->move(-2*CELL_SIZE, CELL_SIZE, false);
            }
        }
    }
    
    // Mario Left Moving
    if (__motionMask & BIT_MASK_LEFT_MOVING) {
        for (int i = 0; i < controllees.size(); ++i) {
            Displayable *d = controllees[i];
            if (d->getType() == MARIO) {
                if (((Character*)d)->getState() != Character::RUNNING) {
                    ((Character*)d)->setState(Character::RUNNING);
                }
                if (runSpeed < 5) {
                    ((Character*)d)->incrementInactivatedState();
                    if ( ((Character*)d)->getInactivatedState() == 0 ) {
                        ((Character*)d)->moveBy(-1*(int)(Utils::now()-__lastTime)/8000*runSpeed, 0);
                    }
                } else {
                     ((Character*)d)->moveBy(-1*(int)(Utils::now()-__lastTime)/8000*(runSpeed-4), 0);
                }
            }
        }
    }
    
    // Mario Right Moving
    if (__motionMask & BIT_MASK_RIGHT_MOVING) {
        for (int i = 0; i < controllees.size(); ++i) {
            Displayable *d = controllees[i];
            if (d->getType() == MARIO) {
                if (((Character*)d)->getState() != Character::RUNNING) {
                    ((Character*)d)->setState(Character::RUNNING);
                }
                if (runSpeed < 5) {
                    ((Character*)d)->incrementInactivatedState();
                    if ( ((Character*)d)->getInactivatedState() == 0 ) {
                        ((Character*)d)->moveBy((int)(Utils::now()-__lastTime)/8000*runSpeed, 0);
                    }
                } else {
                    ((Character*)d)->moveBy((int)(Utils::now()-__lastTime)/8000*(runSpeed-4), 0);
                }

            }
        }
    }
    
    // Mario Jumping
    if ((__motionMask & BIT_MASK_JUMPING) && !(__motionMask & BIT_MASK_FREE_FALLING)) {
        this->handleJump();
    }
    
    // Detect free fall
    if (!(__motionMask & BIT_MASK_JUMPING)) {
        for (int i = 0; i < controllees.size(); ++i) {
            Displayable *d = controllees[i];
            if (d->getType() == MARIO) {
                if ( __motionMask & BIT_MASK_FREE_FALLING || ( ((Character*)d)->moveBy(0, 1) && ((Character*)d)->moveBy(0, -1) )) {
                    if (!__timeWhenMovementBegan) {
                        __timeWhenMovementBegan = Utils::now();
                        ((Character*)d)->setPosAndSizeBeforeJumping();
                    }
                    if (((Character*)d)->getState() != Character::JUMPING) {
                        ((Character*)d)->setState(Character::JUMPING);
                        __motionMask |= BIT_MASK_FREE_FALLING;
                        
                    }
                    int ret = ((Character*)d)->jump(__timeWhenMovementBegan, 0, 0, jumpSpeed); // check whether d is still jumping
                    if (ret) { // if not, stop.
                        __motionMask &= ~BIT_MASK_FREE_FALLING;
                        __timeWhenMovementBegan = 0;
                        velosityScale.first = velosityScale.second = 1;
                        ((Character*)d)->setState(Character::STANDING);
                        double vx = ((Character*)d)->getVelosity().first;
                        double vy = ((Character*)d)->getVelosity().second;
                        bool dir = ((Character*)d)->getDirection();
                        ((Character*)d)->setVelosity((dir?vx>0:vx<0)?vx:-vx, vy);
                    }
                    
                }
            }
        }
    } // if
    
    // 
}



void EventListener::lookupKeySymbol() {
    char text[BUFFER_SIZE];
	XLookupString(
                  (XKeyEvent *)&event, 	// the keyboard event
                  text, 					// buffer when text will be written
                  BUFFER_SIZE, 			// size of the text buffer
                  &key, 					// workstation-independent key symbol
                  NULL );
}

void EventListener::registerDisplayable(Displayable *d) {
    if (inControlles(d) == -1) {
        controllees.push_back(d);
    }
}

void EventListener::unregisterDisplayable(Displayable *d) {
    int index;
    if ((index = inControlles(d)) != -1) {
        controllees.erase(controllees.begin()+index);
    }
}

void EventListener::start() {
INTRO:
    while (!__stopSignal) {
        XInfo &xInfo = canvas->getXInfo();
		if (XPending(xInfo.display) > 0) {
			XNextEvent( xInfo.display, &event );
			switch( event.type ) {
                case KeyPress:
                    std::cout << "Pressed!!" << std::endl;
                    lookupKeySymbol();
                    switch (key) {
                        case SPACE_KEY: {
                            std::vector<Displayable*> dlist = canvas->getDlist();
                            for (int i = 0; i < dlist.size(); ++i) {
                                if (dlist[i]->getType() == INTROTEXT) {
                                    dlist[i]->setNeedsPaint(false);
                                    break;
                                }
                            }
                            stop();
                            break;
                        }
                        case Q_KEY:case EXC_KEY:
                            goto END;
                            break;
                            
                        default:
                            break;
                    }
                    break;
				case ConfigureNotify:
                    handleResize();
					break;
                case Expose:
                    break;
                default:
                    ;
			}
		}
        __lastTime = Utils::now();
		usleep(1000000/fps);
		canvas->repaint();
    }
PLAY:
    __stopSignal = false;
    while (!__stopSignal) {
        XInfo &xInfo = canvas->getXInfo();
//        fprintf(stderr, "eventloop running...");
		if (XPending(xInfo.display) > 0) {
            prevEvent = event;
			XNextEvent( xInfo.display, &event );
			switch( event.type ) {
				case KeyPress:
                    std::cout << "Pressed!!" << std::endl;
                    __keyHeldDown = true;
                    prevKey = key;
                    lookupKeySymbol();
                    if (key == SPACE_KEY) {
                        std::vector<Displayable*> dlist = canvas->getDlist();
                        for (int i = 0; i < dlist.size(); ++i) {
                            if (dlist[i]->getType() == INTROTEXT) {
                                dlist[i]->setNeedsPaint(true);
                                break;
                            }
                        }
                        goto INTRO;
                    }
					handleKeyPress();
					break;
                case KeyRelease:
                    std::cout << "Released!!" << std::endl;
                    __keyHeldDown = false;
                    handleKeyRelease();
                    break;
				case ConfigureNotify:
                    handleResize();
//                    resize = true;
					break;
                case Expose:
                    break;
                default:
                    ;
			}
		}
        handleAnimation();
		canvas->repaint();
        __lastTime = Utils::now();
		usleep(1000000/fps);
		
    }
END:;
}

void EventListener::stop() {
    __stopSignal = true;
}
