#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    // playerPos.pos->x = mainGameMechsRef -> getBoardSizeX ()/2;
    // playerPos.pos->y = mainGameMechsRef -> getBoardSizeY ()/2;
    // playerPos.symbol = '@';

    //Updated for iteration 3
    //playerPosList.insertTail(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@'));

    // edit by Bishal 
    
    playerPosList = new objPosArrayList();
    objPos initialPosition(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '@');
    playerPosList->insertHead(initialPosition);
    
}


Player::~Player()
{
    // delete any heap members here 
    delete playerPosList;
}

objPos Player::getPlayerPos() const // upgraded for iteration 3
{
    // return the reference to the playerPos arrray list
    return playerPosList->getHeadElement(); 
}


void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    
    if(input!='\0'){
        switch(input)
        {     
            // case 27: // Escape key to exit
            //     mainGameMechsRef->setExitTrue();
            //     break;                 
            case 'w':  // up
                if (myDir != DOWN) {  
                    myDir = UP;
                }
                break;

            case 'a':  // left
                if (myDir != RIGHT) {  
                    myDir = LEFT;
                }
                break;
            case 's':  // down
                if (myDir != UP) {  
                    myDir = DOWN;
                }   
                break;
            case 'd':  // right
                if (myDir != LEFT) {  
                    myDir = RIGHT;
                }
                break;
            case 9: //Tab key to stop the snake
                myDir = STOP;
                break;
        }
        mainGameMechsRef->clearInput(); // clears input 
    }
}


void Player::movePlayer(bool foodConsumed)
{
    // Calculate new head position based on direction
    int newX = playerPosList->getHeadElement().pos->x;
    int newY = playerPosList->getHeadElement().pos->y;
    
    // PPA3 Finite State Machine logic
    switch (myDir){
           case UP:    
            newY--; // initial code snipped 

            /*
            // reference code 
            //newY = (headPos.pos->y - 1) > 0 ? headPos.pos->y - 1 : mainGameMechsRef->getBoardSizeY() - 2; 
            if ((headPos.pos->y - 1) > 0) 
            {
                newY = headPos.pos->y - 1;
            }
            else 
            {
                newY = mainGameMechsRef->getBoardSizeY() - 2;
            }
            */ 
            break;
        case DOWN:  
            newY++; 
            break;
        case LEFT:  
            newX--; 
            break;
        case RIGHT: 
            newX++; 
            break;
        default:    
            return;            
            
    }

    // Apply wrap-around logic
    int boardWidth = mainGameMechsRef->getBoardSizeX();
    int boardHeight = mainGameMechsRef->getBoardSizeY();

     if (newX < 1) {
        newX = boardWidth - 2;
     }
    else if (newX >= boardWidth - 1) {
        newX = 1;
    }
    if (newY < 1) {
        newY = boardHeight - 2;
    }
    else if (newY >= boardHeight - 1) {
        newY = 1;
    }

    // Insert new head position
    playerPosList->insertHead(objPos(newX, newY, '@'));


    // Remove the tail unless food was consumed
    if (!foodConsumed) {
        playerPosList->removeTail();
    }
    

}

// More methods to be added
objPosArrayList* Player::getPlayerPosListRef() const
{
    return playerPosList;
}