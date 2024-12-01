#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included

    playerPos.pos->x = 10;
    playerPos.pos->y = 10;
    playerPos.symbol = '@';

}


Player::~Player()
{
    // delete any heap members here (LEAVE EMPTY FOR NOW)
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}



void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if(input!='\0'){
        switch(input)
        {     
            case 27: // Escape key to exit
                mainGameMechsRef->setExitTrue();
                break;                 
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
    }
}
void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added