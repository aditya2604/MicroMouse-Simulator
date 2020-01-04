
#include "micromouseserver.h"
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
    //Two integer variables to store X and Y coordinates of current position of mouse returned from findxPos() and findyPos() respectively.
    int xPos;
    int yPos;
    xPos = findxPos();
    yPos = findyPos();

    /*After running the program multiple times in the maze, these points are data that have been collected where decision making has to be different.
     *In an actual AI/ML program, these coordinates and corresponding decision would have been learned by training the AI/ML model.*/
    if ((xPos == 4) && (yPos == 9))
    {
        turnRight();
        moveForward();
    }
    else if ((xPos == 6) && (yPos == 10))
    {
        turnRight();
        moveForward();
    }
    else if ((xPos == 19) && (yPos == 17))
    {
        turnRight();
        moveForward();
    }
   else if ((xPos == 10) && (yPos == 9))
    {
        turnRight();
        moveForward();
    }
    else if ((xPos == 12) && (yPos == 10))
    {
        turnRight();
        moveForward();
    }
   else if ((xPos == 7) && (yPos == 10))
    {
        //In order to reduce the amount of move forward calls.
        moveForward();
    }

    //When the mouse reaches these coordinates, it has solved the maze.
    else if ((xPos == 12) && (yPos == 8))
    {
        foundFinish();
        printUI("The maze has been solved!");
    }

    /*The mouse will check first to see if there is a wall on the left. If there is no wall, it will go left.
     *If there is a wall on the left, the mouse will check if there is a wall on the right. If there's no wall on the right, it will go right.
     *If there is a wall to the left and right but no wall on the front, the mouse will move forward.
     *If there is a wall to the left, right, and in front of the mouse, the mouse will turn right twice to face the opposite direction.*/

    else if (isWallLeft() == false)
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
        //Turning the mouse to the opposite direction.
        turnRight();
        turnRight();
    }
    //If none of those conditions are carried out, then the mouse will just move forward.
    else moveForward();
}
