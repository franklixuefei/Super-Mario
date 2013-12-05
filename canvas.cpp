//
//  canvas.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-18.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "canvas.h"

Canvas::Canvas(int argc, char* argv[], int width, int height) : g(new Grid()) {
    /*
     * Display opening uses the DISPLAY	environment variable.
     * It can go wrong if DISPLAY isn't set, or you don't have permission.
     */
    
    xInfo.width = width;
    xInfo.height = height;
    
    xInfo.display = XOpenDisplay( "" );
    if ( !xInfo.display )	{
        Static::error( "Can't open display." );
    }
    
    /*
     * Find out some things about the display you're using.
     */
    xInfo.screen = DefaultScreen( xInfo.display ); // macro to get default screen index

    XColor xcolour;
    Colormap cmap;
    char color_vals[15][20]={"white", "black", "red", "green", "blue", "cyan", "yellow", "magenta", "orange", "brown", "gray", "light sky blue", "gainsboro", "dim gray", "antique white"};
    
    cmap=DefaultColormap(xInfo.display,DefaultScreen(xInfo.display));
    for(int i=0; i < 15; ++i) {
        if (!XParseColor(xInfo.display,cmap,color_vals[i],&xcolour)) {
            std::cerr << "Bad colour: " << color_vals[i] << std::endl;
        }
        if (!XAllocColor(xInfo.display,cmap,&xcolour)) {
            std::cerr << "Bad colour: " << color_vals[i] << std::endl;
        }
        xInfo.colours[i]=xcolour.pixel;
    }

    
    xInfo.window = XCreateSimpleWindow(
                                       xInfo.display,				// display where window appears
                                       DefaultRootWindow( xInfo.display ), // window's parent in window tree
                                       0, 0,			           // upper left corner location
                                       width, height,	               // size of the window
                                       3,						     // width of window's border
                                       xInfo.colours[xInfo.Black],						// window border colour
                                       xInfo.colours[xInfo.White] );					    // window background colour
    // extra window properties like a window title
    XSetStandardProperties(
                           xInfo.display,		// display containing the window
                           xInfo.window,		// window whose properties are set
                           "Super Mario Bros",	// window's title
                           None,				// icon's title
                           None,				// pixmap for the icon
                           argv, argc,			// applications command line args
                           None );			// size hints for the window
    
    /*
     * Put the window on the screen.
     */
    
    XSelectInput(xInfo.display, xInfo.window, ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask);
    
    XAutoRepeatOff(xInfo.display);
    
    XMapRaised( xInfo.display, xInfo.window );
    XFlush(xInfo.display);
    sleep(2);
    xInfo.pixmap = XCreatePixmap(xInfo.display,xInfo.window,width,
                               height,DefaultDepth(xInfo.display,DefaultScreen(xInfo.display)));
    xInfo.gc = XCreateGC(xInfo.display, xInfo.window, 0,(XGCValues *)0);
    
    
        
    XSetForeground(xInfo.display, xInfo.gc, xInfo.colours[xInfo.Black]);
    
    XSetBackground(xInfo.display, xInfo.gc, xInfo.colours[xInfo.White]);
    
//    XDrawArc(display, window, gc, 100, 100, 30, 30, 0, 360*64);
    
    XFlush(xInfo.display);
    sleep(2);	// let server get set up before sending drawing commands
}

Canvas::~Canvas() {
    XFreeGC(xInfo.display, xInfo.gc);
    XFreePixmap(xInfo.display, xInfo.pixmap);
    XCloseDisplay(xInfo.display);
    for (int i = 0; i < dlist.size(); ++i) {
        if (dlist[i]) delete dlist[i];
    }
}

void Canvas::paintAll() {
    std::vector<Displayable*>::const_iterator begin = dlist.begin();
    std::vector<Displayable*>::const_iterator end = dlist.end();
    
    while( begin != end ) {
        Displayable* d = *begin;
        if (d->getNeedsPaint()) {
            d->paint(xInfo);
        }
        begin++;
    }
#if DOUBLE_BUFFERING
    XCopyArea(xInfo.display, xInfo.pixmap, xInfo.window, xInfo.gc,
              0, 0, WINDOW_DEFAULT_WIDTH, WINDOW_DEFAULT_HEIGHT,  // region of pixmap to copy
              xInfo.width/2-WINDOW_DEFAULT_WIDTH/2, xInfo.height/2-WINDOW_DEFAULT_HEIGHT/2); // position to put top left corner of pixmap in window
#endif
    XFlush( xInfo.display );
}

void Canvas::repaint() {
    XClearWindow( xInfo.display, xInfo.window );
    this->paintAll();
}

void Canvas::paintTerrainStripe(float x, int height) {
    for (int i = 1; i <= height; ++i) {
        DRect drect;
        drect.x = x * CELL_SIZE;
        drect.y = (MAX_ROWS - i) * CELL_SIZE;
        drect.width = drect.height = CELL_SIZE-1;
        std::vector<Cell*> cells;
        DType dtype = BLOCK;
        Block *d = new Block(drect, dtype, cells, this);
        dlist.push_back(d);
#if LOAD_IMAGE
        d->loadBitmap(xInfo);
#endif
        d->solidifyOccupiedCells();
    }
}

void Canvas::initIntro() {
    DRect drect;
    drect.x = 0;
    drect.y = 0;
    drect.width = WINDOW_DEFAULT_WIDTH;
    drect.height = WINDOW_DEFAULT_HEIGHT/2;
    std::vector<Cell*> cells;
    DType dtype = INTROTEXT;
    IntroText *d = new IntroText(drect, dtype, cells, this);
    dlist.push_back(d);
}

void Canvas::initUnderlay() {
    DRect drect;
    drect.x = 0;
    drect.y = 0;
    drect.width = WINDOW_DEFAULT_WIDTH;
    drect.height = WINDOW_DEFAULT_HEIGHT;
    std::vector<Cell*> cells;
    DType dtype = UNDERLAY;
    CanvasUnderlay *d = new CanvasUnderlay(drect, dtype, cells, this);
    dlist.push_back(d);
}

void Canvas::initTerrain() {
    srand(getpid());
    int prevHeight = (int)rand()%7;
    int height = 0;
    for (int i = 0; i < MAX_COLUMNS; ++i) {
        if (i <= 3) {
            height = 5-i;
        } else {
            do {
                height = (int)rand()%7;
            } while (height - prevHeight > 2);
        }
        prevHeight = height;
        this->paintTerrainStripe((float)i, height);
    }
}

Character* Canvas::initCharacter() {
    DRect drect;
    drect.x = 0;
    drect.y = 0;
    drect.width = CELL_SIZE-1;
    drect.height = 2 * CELL_SIZE-1;
    std::vector<Cell*> cells;
    DType dtype = MARIO;
    Character *d = new Character(drect, dtype, cells, this);
    dlist.push_back(d);
    d->solidifyOccupiedCells();
    while (d->moveBy(0, 1)) {} // drop mario to the ground :-)
    return d;
}

void Canvas::initEnemies() {
//    int increment = rand()%4+1;
//    for (int i = 1; i < MAX_COLUMNS; i+=increment) {
//        for (int j = 0; j < MAX_ROWS; ++j) {
//            if (g->getCell(j, i).isSolid()) {
//                DRect drect;
//                drect.x = i*CELL_SIZE;
//                drect.y = (j-1)*CELL_SIZE;
//                drect.width = CELL_SIZE-1;
//                drect.height = CELL_SIZE-1;
//                std::vector<Cell*> cells;
//                DType dtype = ENEMY;
//                Enemy *e = new Enemy(drect, dtype, cells, this);
//                dlist.push_back(e);
//                e->solidifyOccupiedCells();
//                break;
//            }
//        }
//    }
}

void Canvas::initFoods() {
    
}

void Canvas::resetCharacter() {
    for (int i = 0; i < dlist.size(); ++i) {
        if (dlist[i]->getType() == MARIO) {
            ((Character*)dlist[i])->setState(Character::STANDING);
            ((Character*)dlist[i])->setDirection(true);
            ((Character*)dlist[i])->move(0, 0);
            while (((Character*)dlist[i])->moveBy(0, 1)) {}
        }
    }
    
}

Sun* Canvas::initSun() {
    srand(getpid());
    DRect drect;
    int min = 2*CELL_SIZE;
    int max = WINDOW_DEFAULT_WIDTH-4*CELL_SIZE;
    drect.x = rand()%(max-min)+min;
    drect.y = CELL_SIZE;
    drect.width = 2*CELL_SIZE;
    drect.height = 2*CELL_SIZE;
    DType dtype = SUN;
    std::vector<Cell*> cells;
    Sun *s = new Sun(drect, dtype, cells, this);
    dlist.push_back(s);
    return s;
}

void Canvas::drawGrid() {
    for (int i = 0; i < MAX_ROWS; ++i) {
        for (int j = 0; j < MAX_COLUMNS; ++j) {
            Cell &cell = g->getCell(i, j);
            CCoords cellCoords = cell.getCoords();
            fprintf(stderr, "Coordinates: X: %d, Y:%d\n", cellCoords.x, cellCoords.y);
            std::ostringstream oss;
            oss << "(" << cellCoords.x << "," << cellCoords.y << ")";
#if DOUBLE_BUFFERING
            XDrawString(xInfo.display, xInfo.pixmap, DefaultGC(xInfo.display, xInfo.screen), cellCoords.x, cellCoords.y+20, oss.str().c_str(), (int)oss.str().length());
            XDrawRectangle(xInfo.display, xInfo.pixmap, xInfo.gc, cellCoords.x, cellCoords.y, CELL_SIZE, CELL_SIZE);
#else
            XDrawString(xInfo.display, xInfo.window, DefaultGC(xInfo.display, xInfo.screen), cellCoords.x, cellCoords.y+20, oss.str().c_str(), (int)oss.str().length());
            XDrawRectangle(xInfo.display, xInfo.window, xInfo.gc, cellCoords.x, cellCoords.y, CELL_SIZE, CELL_SIZE);
#endif

        }
    }
    XFlush(xInfo.display);
    
}

Grid* Canvas::getGrid() const{
    return g;
}

std::vector<Displayable*> Canvas::getDlist() const {
    return dlist;
}

void Canvas::eraseDlistElem(int i) {
    dlist.erase(dlist.begin()+i);
}

unsigned long Canvas::getColour(unsigned long colour) const{
    return xInfo.colours[colour];
}

XInfo& Canvas::getXInfo() {
    return xInfo;
}
