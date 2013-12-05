//
//  displayable.cpp
//  cs349-a1
//
//  Created by Frank Li on 2013-09-17.
//  Copyright (c) 2013 Xuefei Li. All rights reserved.
//

#include "displayable.h"
#include "canvas.h"
DRect::DRect() : width(CELL_SIZE), height(CELL_SIZE) {}

Displayable::Displayable(DRect drect, DType dtype, std::vector<Cell*> cells, Canvas* canvas) : posAndSize(drect), type(dtype), cells(cells), canvas(canvas), needsPaint(true) {
    offset.x = offset.y = 0;
}

Displayable::~Displayable() {}

std::vector<Cell*> Displayable::calculateInvolvedCells() {
    std::vector<Cell*> involvedCells;
    RelCoords topLeftCoord, topRightCoord, bottomLeftCoord, bottomRightCoord;
    topLeftCoord.x = (posAndSize.x)/CELL_SIZE;
    topLeftCoord.y = (posAndSize.y)/CELL_SIZE;
    topRightCoord.x = (posAndSize.x+posAndSize.width)/CELL_SIZE;
    topRightCoord.y = (posAndSize.y)/CELL_SIZE;
    bottomLeftCoord.x = (posAndSize.x)/CELL_SIZE;
    bottomLeftCoord.y = (posAndSize.y+posAndSize.height)/CELL_SIZE;
    bottomRightCoord.x = (posAndSize.x+posAndSize.width)/CELL_SIZE;
    bottomRightCoord.y = (posAndSize.y+posAndSize.height)/CELL_SIZE;
#if XDEBUG
    fprintf(stderr, "For DType %d, top left point is in cell of coordinate (%d, %d); top right point is in cell of coordinate (%d, %d); bottom left point is in cell of coordinate (%d, %d); bottom right point is in cell of coordinate (%d, %d). All coordinates are relative to the grid.\n", type, topLeftCoord.x, topLeftCoord.y, topRightCoord.x, topRightCoord.y, bottomLeftCoord.x, bottomLeftCoord.y, bottomRightCoord.x, bottomRightCoord.y);
#endif
    for (int i = topLeftCoord.y; i <= bottomLeftCoord.y && i < MAX_ROWS; ++i) {
        for (int j = topLeftCoord.x; j <= topRightCoord.x && j < MAX_COLUMNS; ++j) {
            Cell &cell = canvas->getGrid()->getCell(i, j);
            involvedCells.push_back(&cell);
        }
    }
    return involvedCells;
}

void Displayable::updateInvolvedCells(std::vector<Cell *> involvedCells) {
    cells.clear();
    for (int i = 0; i < involvedCells.size(); ++i) {
        cells.push_back(involvedCells[i]);
    }
}


void Displayable::setCellsSolid(bool solid) {
    for (int i = 0; i < cells.size(); ++i) {
        cells[i]->setSolid(solid, type);
        if (solid) {
            cells[i]->setDisplayable(this);
        } else {
            cells[i]->setDisplayable(NULL);
        }
    }
}

void Displayable::paint(XInfo &xInfo) {}

#if XDEBUG
void Displayable::debug() {}
#endif

void Displayable::solidifyOccupiedCells() {
    this->setCellsSolid(false); // first, set all previously involved cells not solid
    std::vector<Cell*>involvedCells = this->calculateInvolvedCells();// calculate newly involved cells
    this->updateInvolvedCells(involvedCells);
    this->setCellsSolid(true); // third, set all newly involved cells solid

}

Cell* Displayable::collisionDetection() {
    std::vector<Cell*>involvedCells = this->calculateInvolvedCells();
    for (int i = 0; i < involvedCells.size(); ++i) {
        if (involvedCells[i]->getDisplayable() && involvedCells[i]->getDisplayable()->getType() == ENEMY) {
            std::cout << "Mario Dead..." << std::endl;
            canvas->resetCharacter();
        }
        if (involvedCells[i]->getDisplayable() != this && involvedCells[i]->isSolid()) {
            return involvedCells[i];
        }
    }
    return NULL;
};

bool Displayable::moveBy(int x, int y, bool shouldSolidifyCells) {
    posAndSize.x += x;
    posAndSize.y += y;
    if (shouldSolidifyCells) {
        Cell *c = this->collisionDetection();
        
#if XDEBUG
        if (c) {
            CCoords cc = c->getCoords();
            std::cerr << "overlapped cell coords: X: " << cc.x << " and Y: " <<  cc.y << std::endl;
        }
#endif
        if (c) {
//            CCoords cc = c->getCoords();
//            if (posAndSize.x + posAndSize.width > cc.x) { // right
//                while (this->collisionDetection()) {
//                    posAndSize.x--;
//                    std::cerr << "right collision" << std::endl;
//                }
//            }
//            if (posAndSize.x < cc.x + CELL_SIZE-1) { // left
//                while (this->collisionDetection()) {
//                    posAndSize.x++;
//                    std::cerr << "right collision" << std::endl;
//                }
//            }
//            if (posAndSize.y + posAndSize.height < cc.y) { // bottom
//                while (this->collisionDetection()) {
//                    posAndSize.y--;
//                    std::cerr << "right collision" << std::endl;
//                }
//            }
//            if (posAndSize.y > cc.y + CELL_SIZE-1) { // top
//                while (this->collisionDetection()) {
//                    posAndSize.y++;
//                    std::cerr << "right collision" << std::endl;
//                }
//            }
            posAndSize.x -= x;
            posAndSize.y -= y;
            return false;
        }
        this->solidifyOccupiedCells();
    }
    return true;
} // paint will be called after this function

bool Displayable::move(int x, int y, bool shouldSolidifyCells) {
    posAndSize.x = x;
    posAndSize.y = y;
    if (shouldSolidifyCells) {
        Cell *c = this->collisionDetection(); // may never get called. Depends on how to use this function.
        if (c) {
            while (this->collisionDetection()) {
                posAndSize.y--;
            }
            return false;
        }
        this->solidifyOccupiedCells();
    }
    return true;
}

bool Displayable::jumpTrajectory(int x, int y) {
    posAndSize.x = posAndSizeBeforeJumping.x + x;
    posAndSize.y = posAndSizeBeforeJumping.y + y;
#if XDEBUG
    fprintf(stderr, "position Y: %d\n\n\n", posAndSize.y);
#endif
    Cell *c = this->collisionDetection();
    if (c) {
        while (this->collisionDetection()) {
            posAndSize.y--;
        }
        return false;
    }
    this->solidifyOccupiedCells();
    if (posAndSize.y > WINDOW_DEFAULT_HEIGHT + 100) {
        std::cout << "Mario Dead..." << std::endl;
        canvas->resetCharacter();
        return false;
    }
    return true;
}

void Displayable::loadBitmap(XInfo &xInfo) {}

DType Displayable::getType() const {
    return type;
}

void Displayable::setPosAndSizeBeforeJumping() {
    posAndSizeBeforeJumping.x = posAndSize.x;
    posAndSizeBeforeJumping.y = posAndSize.y;
    posAndSizeBeforeJumping.width = posAndSize.width;
    posAndSizeBeforeJumping.height = posAndSize.height;
}

int Displayable::getInactivatedState() {
    return inactivated;
}

void Displayable::incrementInactivatedState() {}

void Displayable::updateOffset(int x, int y) {
    this->offset.x = x;
    this->offset.y = y;
}

bool Displayable::getNeedsPaint() const{
    return needsPaint;
}

void Displayable::setNeedsPaint(bool paint) {
    needsPaint = paint;
}