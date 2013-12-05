//
//  mario.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "mario.h"

Mario::Mario(int argc, char* argv[]) {
    unsigned int runSpeed;
    unsigned int jumpSpeed;
    unsigned int sunSpeed;
    unsigned int fps;
    switch (argc) {
        case 5:
            runSpeed = atoi(argv[1]); // 1-10
            jumpSpeed = atoi(argv[2]); // 1-10
            sunSpeed = atoi(argv[3]); // 1-10
            fps = atoi(argv[4]); // 10-100
            break;
        case 4:
            runSpeed = atoi(argv[1]);
            jumpSpeed = atoi(argv[2]);
            sunSpeed = atoi(argv[3]);
            fps = FPS;
            break;
        case 3:
            runSpeed = atoi(argv[1]);
            jumpSpeed = atoi(argv[2]);
            sunSpeed = SUN_SPEED;
            fps = FPS;
            break;
        case 2:
            runSpeed = atoi(argv[1]);
            jumpSpeed = JUMP_SPEED;
            sunSpeed = SUN_SPEED;
            fps = FPS;
            break;
        case 1:default:
            runSpeed = RUN_SPEED;
            jumpSpeed = JUMP_SPEED;
            sunSpeed = SUN_SPEED;
            fps = FPS;
            break;
    }
    if (runSpeed < 1 || runSpeed > 10 || jumpSpeed < 1 || jumpSpeed > 10 || sunSpeed < 1 || sunSpeed > 10 || fps < 10 || fps > 100) {
        std::cerr << "Usage: " << argv[0] << " [run speed (1 - 10)] [jump speed (1 - 10)] [sun speed (1 - 10)] [FPS (10 - 100)]" << std::endl << "run, jump, and sun speeds are default to 5" << std::endl << "FPS is default to 60" << std::endl;
        exit(1);
    }
    canvas = new Canvas(argc, argv);
    eventListener = new EventListener(canvas, fps, runSpeed, sunSpeed, jumpSpeed);
}

void Mario::start() {
    fprintf(stdout, "Mario Bros started...");
#if XDEBUG
#if DRAW_GRID
    canvas->drawGrid();
#endif
#endif
    canvas->initUnderlay();
    canvas->initTerrain();
    Sun *s = canvas->initSun();
    Character* c = canvas->initCharacter();
    canvas->initEnemies();

    canvas->paintAll();
    
    canvas->initIntro();
    
    eventListener->registerDisplayable(c);
    eventListener->registerDisplayable(s);
    eventListener->start();
}

Mario::~Mario() {
    std::cerr << "Game destructred" << std::endl;
    delete canvas;
}
