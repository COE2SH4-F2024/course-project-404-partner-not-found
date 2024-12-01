#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

#include "Player.h"
#include "GameMechs.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // global variable to instantiate player obj 
GameMechs *myGM;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM -> getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    myGM = new GameMechs(); //default setting
    myPlayer = new Player(myGM);

    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        myGM->setInput(input); // Set the input in the GameMechs object
    
    }
}

void RunLogic(void)
{
    char input = myGM->getInput(); // Retrieve input
    if (input == '!') { 
        myGM->setExitTrue(); // Exit the game
    }
    
    myPlayer->updatePlayerDir(); // Update player direction
    myPlayer->movePlayer();      // Move the player based on the direction

    

    myGM->clearInput(); // Clear the input to prevent re-processing  
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    objPos playerPos = myPlayer -> getPlayerPos();

    MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);

    int row, col;
    int boardWidth = myGM->getBoardSizeX();
    int boardHeight = myGM->getBoardSizeY();

    for (row = 0; row < boardHeight; row++) {
        for (col = 0; col < boardWidth; col++) {
            // if we're on the border
            if (row == 0 || row == boardHeight - 1 || col == 0 || col == boardWidth - 1) {
                MacUILib_printf("#");  // Border character
            }
            // if we're at the player's position
            else if (row == playerPos.pos->y && col == playerPos.pos->x) {
                MacUILib_printf("%c", playerPos.symbol);  // Player character
            }
            // Otherwise, print a space
            else {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");  // Move to the next row
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;

    MacUILib_uninit();
}
