#include <iostream>
#include "MacUILib.h"

#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include "food.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; // global variable to instantiate player obj 
GameMechs *myGM;
Food *myFood;

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
    myFood = new Food(myGM->getBoardSizeX(), myGM->getBoardSizeY());
}

void GetInput(void)
{
    if (MacUILib_hasChar()) {
        char input = MacUILib_getChar();
        myGM->setInput(input); // Set the input in the GameMechs object

        // Adjust speed if '=' or '-' is pressed
        if (input == '=') {
            myGM->setSpeed(myGM->getSpeed() - 10000); // Increase speed (reduce delay)
        } else if (input == '-') {
            myGM->setSpeed(myGM->getSpeed() + 10000); // Decrease speed (increase delay)
        }
    
    }
}

void RunLogic(void)
{
    char input = myGM->getInput(); // Retrieve input
    if (input == '!') { 
        myGM->setExitTrue(); // Exit the game
    }
    
    myPlayer->updatePlayerDir(); // Update player direction
    //myPlayer->movePlayer();      // Move the player based on the direction

    //objPos playerPos = myPlayer -> getPlayerPos();

    objPos playerHead = myPlayer->getPlayerPosListRef()->getHeadElement();
    objPos foodPos = myFood->getFoodPos();

    if (playerHead.pos->x == foodPos.pos->x && playerHead.pos->y == foodPos.pos->y) {
        //myPlayer->movePlayer(true); // Grow the snake
        myGM->incrementScore(); // Increase score
        myFood->generateFood(myPlayer->getPlayerPosListRef()); // Generate new food
    }

    myPlayer->movePlayer(playerHead.pos->x == foodPos.pos->x && playerHead.pos->y == foodPos.pos->y); 
    myGM->clearInput(); // Clear the input to prevent re-processing  
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    

    //Creating objects
    //objPos playerPos = myPlayer -> getPlayerPos(); //from iteration 2, commented out
    const objPosArrayList* snakeBody = myPlayer->getPlayerPosListRef();
    objPos foodPos = myFood -> getFoodPos();

    int row, col;
    int boardWidth = myGM->getBoardSizeX();
    int boardHeight = myGM->getBoardSizeY();

    MacUILib_printf("===========Snake Game===========\n\n");
    MacUILib_printf("Press = to increase speed\n");
    MacUILib_printf("Press - to decrease speed\n\n");

    for (row = 0; row < boardHeight; row++) {
        for (col = 0; col < boardWidth; col++) {
            bool isDrawn = false;

            // Draw borders
            if (row == 0 || row == myGM->getBoardSizeY() - 1 || col == 0 || col == myGM->getBoardSizeX() - 1) {
                MacUILib_printf("%c", '#'); // Border symbol
                isDrawn = true;
            }

            // Draw food
            else if (!isDrawn && row == foodPos.pos->y && col == foodPos.pos->x) {
                MacUILib_printf("%c", foodPos.symbol); // Food symbol
                isDrawn = true;
            }

            // Draw snake body
            else if (!isDrawn) {
                for (int i = 0; i < snakeBody->getSize(); ++i) {
                    objPos segment = snakeBody->getElement(i);

                    if (row == segment.pos->y && col == segment.pos->x) {
                        MacUILib_printf("%c", segment.symbol); // Snake body symbol
                        isDrawn = true;
                        break;
                    }
                }
            }

            // Draw empty space
            if (!isDrawn) {
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");  // Move to the next row
    }

    //Print Statements
    MacUILib_printf("\nYour Score: %d\n", myGM->getScore());
    MacUILib_printf("Speed Delay: %d ms\n", myGM->getSpeed());

    //MacUILib_printf("\nPlayer [x, y, symbol] = [%d, %d, %c]\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
    MacUILib_printf("Food [x, y, symbol] = [%d, %d, %c]\n", foodPos.pos->x, foodPos.pos->y, foodPos.symbol);
    


}

void LoopDelay(void)
{
    //MacUILib_Delay(DELAY_CONST); // 0.1s delay
    MacUILib_Delay(myGM->getSpeed());
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;
    delete myFood;

    MacUILib_uninit();
}
