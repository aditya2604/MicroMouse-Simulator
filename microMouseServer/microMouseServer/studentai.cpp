
#include "micromouseserver.h"
#include <iostream>
using namespace std;
void microMouseServer::studentAI()
{
/*
 * The following are the eight functions that you can call. Feel free to create your own fuctions as well.
 * Remember that any solution that calls moveForward more than once per call of studentAI() will have points deducted.
 *
 *The following functions return if there is a wall in their respective directions
 *bool isWallLeft();
 *bool isWallRight();
 *bool isWallForward();
 *int findxPos();
 *int findyPos();
 *
 *The following functions move the mouse. Move forward returns if the mouse was able to move forward and can be used for error checking
 *bool moveForward();
 *void turnLeft();
 *void turnRight();
 *
 * The following functions are called when you need to output something to the UI or when you have finished the maze
 * void foundFinish();
 * void printUI(const char *mesg);
 */
    int xPos;
    int yPos;
    xPos = findxPos();
    yPos = findyPos();

    if ((xPos == 4) && (yPos == 9))
    {
        turnRight();
        moveForward();
    }
    if ((xPos == 6) && (yPos == 10))
    {
        turnRight();
        moveForward();
    }
    if ((xPos == 19) && (yPos == 17))
    {
        turnRight();
        moveForward();
    }
    if ((xPos == 10) && (yPos == 9))
    {
        turnRight();
        moveForward();
    }
    if ((xPos == 12) && (yPos == 10))
    {
        turnRight();
        moveForward();
    }
    if ((xPos == 6) && (yPos == 10))
    {
        moveForward();
    }
    if ((xPos == 12) && (yPos == 8))
    {
        foundFinish();
        printUI("The maze has been solved!");
    }
    if (isWallLeft() == false)
    {
        turnLeft();
        moveForward();
    }
    else if (isWallRight() == false)
    {
        turnRight();
        moveForward();
    }
    else if (isWallForward() == true)
    {
        turnRight();
        turnRight();
    }
    else moveForward();
}
