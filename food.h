#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"
#include <cstdlib>
#include <ctime>

class Food {
private:
    objPos foodPos;
    int boardSizeX;
    int boardSizeY;

public:
    Food(int boardX, int boardY);
    ~Food();

    void generateFood(const objPosArrayList* playerPositions);
    objPos getFoodPos() const;
};

#endif