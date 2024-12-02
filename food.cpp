#include "food.h"

Food::Food(int boardX, int boardY) {
    // Set board dimensions
    boardSizeX = boardX;
    boardSizeY = boardY;

    // Seed random generator for random food generation
    std::srand(std::time(nullptr));

    // Initialize food position to a valid point
    foodPos.setObjPos(1 + std::rand() % (boardSizeX - 2), 1 + std::rand() % (boardSizeY - 2), '*');
}

Food::~Food() {
    // Destructor - nothing to clean up
}

void Food::generateFood(const objPosArrayList& playerPositions) {
    bool validPosition = false;
    int newX, newY;

    // Keep generating a new position until it's valid (i.e., not on the player's body)
    while (!validPosition) {
        newX = 1 + std::rand() % (boardSizeX - 2);
        newY = 1 + std::rand() % (boardSizeY - 2);
        validPosition = true;

        // Check if new position overlaps with any player body part
        for (int i = 0; i < playerPositions.getSize(); ++i) {
            objPos playerPos = playerPositions.getElement(i);
            if (playerPos.pos->x == newX && playerPos.pos->y == newY) {
                validPosition = false;
                break;
            }
        }
    }

    // Set the new food position
    foodPos.setObjPos(newX, newY, '*');
}

objPos Food::getFoodPos() const {
    return foodPos;
}