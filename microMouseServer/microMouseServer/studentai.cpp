#include "micromouseserver.h"
#include <iostream>
using namespace std;
//int isVisited[MAZE_WIDTH+1][MAZE_HEIGHT+1] = {0};
void microMouseServer::initDatabase()
{
    //Initailize isVisited to all 0s before start of program.
    memset(isVisited,0,sizeof(int)*(MAZE_WIDTH+1)*(MAZE_HEIGHT+1));
    //dataBase is a double dimensional array representing the allowed
    //direction of traversal at each element of the grid. The lowest
    //3 bits of each element are used to indicate the allowed directions.
    //in this order - FRL i.e. lowest bit represents Left, second from
    //right stands for Right and third from right stands for forward.
    //Value of 1 at the bit location indicates traversal in the direction
    // is allowed. Value 0 indicates traversal in the direction now allowed.
    //Initialize each element of the array to 7 at the start of the
    //program to indicate all directions allowed.
    for(int i =0; i < MAZE_WIDTH+1; i++)
        for(int j = 0; j < MAZE_HEIGHT+1; j++)
            dataBase[i][j] = 7;
}

//updateDatabase updates the array dataBase to unset a bit corresponding
//to the direction passed as input parameter at the position x & y.
//For example, if at position [0][0], L is not allowed, the this function
//will set 0 at the rightmost bit of dataBase[0][0]. If the value earlier
//was 7, it will change to 6.
void microMouseServer::updateDatabase(int posx, int posy, Direction dir)
{
    cout << "before :" << posx << " " << posy << " " << dataBase[posx][posy] << endl;
    dataBase[posx][posy] &= ~ (1 << dir);
    cout << posx << " " << posy << " " << dataBase[posx][posy] << endl;
}

//checkDatabaseForDecision evaluates if traversal in the given direction at
//the given mouse position is allowed or now. It does so by checking if there is
//1 or 0 at the bit position for directions FRL.
bool microMouseServer::checkDatabaseForDecision(int posx,int posy, Direction dir)
{
    if(dataBase[posx][posy] & (1 << dir))
        return true;
    else
        return false;
}

/* Function isWallLeftEnhanced is an enhanced version of isWallLeft to take into
 * account for isVisited. It returns this logical condition -
 * isWallLeft || isVisited
 */
bool microMouseServer::isWallLeftEnhanced()
{
    baseMapNode *mover = &this->mazeData[this->maze->mouseX()-1][this->maze->mouseY()-1];
    switch (this->maze->mouseDir()) {
    case dUP:
        return (mover->isWallLeft() || (isVisited[findxPos()-1][findyPos()] == 1));
        break;
    case dDOWN:
        return (mover->isWallRight() || (isVisited[findxPos()+1][findyPos()] == 1));
        break;
    case dLEFT:
        return (mover->isWallBottom() || (isVisited[findxPos()][findyPos()-1] == 1));
        break;
    case dRIGHT:
        return (mover->isWallTop() || (isVisited[findxPos()][findyPos()+1] == 1));
        break;
    }
    return true;
}

/* Function isWallRightEnhanced is an enhanced version of isWallRight to take into
 * account for isVisited. It returns this logical condition -
 * isWallRight || isVisited
 */
bool microMouseServer::isWallRightEnhanced()
{
    baseMapNode *mover = &this->mazeData[this->maze->mouseX()-1][this->maze->mouseY()-1];
    switch (this->maze->mouseDir()) {
    case dUP:
        return (mover->isWallRight() || (isVisited[findxPos()+1][findyPos()] == 1));
        break;
    case dDOWN:
        return (mover->isWallLeft() || (isVisited[findxPos()-1][findyPos()] == 1));
        break;
    case dLEFT:
        return (mover->isWallTop() || (isVisited[findxPos()][findyPos()+1] == 1));
        break;
    case dRIGHT:
        return (mover->isWallBottom() || (isVisited[findxPos()][findyPos()-1] == 1));
        break;
    }
    return true;
}

/* Function isWallForwardEnhanced is an enhanced version of isWallForward to take into
 * account for isVisited. It returns this logical condition -
 * isWallForward || isVisited
 */
bool microMouseServer::isWallForwardEnhanced()
{
    baseMapNode *mover = &this->mazeData[this->maze->mouseX()-1][this->maze->mouseY()-1];
    switch (this->maze->mouseDir()) {
    case dUP:
        return (mover->isWallTop() || (isVisited[findxPos()][findyPos()+1] == 1));
        break;
    case dDOWN:
        return (mover->isWallBottom() || (isVisited[findxPos()][findyPos()-1] == 1));
        break;
    case dLEFT:
        return (mover->isWallLeft() || (isVisited[findxPos()-1][findyPos()] == 1));
        break;
    case dRIGHT:
        return (mover->isWallRight() || (isVisited[findxPos()+1][findyPos()] == 1));
        break;
    }

    return true;
}

//Returns true if the closing condition has been met. Else false
//Closing condition is that mouse has followed this patter of turns
// R->L->L && is now facing RIGHT && is allowed to take another
//LEFT i.e. there is no wall on LEFT with the mouse facing RIGHT
bool microMouseServer::closingCondition(int last_turn)
{
    baseMapNode *mover = &this->mazeData[this->maze->mouseX()-1][this->maze->mouseY()-1];
    if ((last_turn == 3) && (this->maze->mouseDir() == dRIGHT) && (mover->isWallTop() == false))
        return true;
    else
        return false;
}

//Returns X coordinate of mouse(mouseX)
int microMouseServer::findxPos()
{
    return this->maze->mouseX();
}

//Returns Y coordinate of mouse(mouseY)
int microMouseServer::findyPos()
{
    return this->maze->mouseY();
}

/* How studentAI solves the maze - studentAI implements an actual AI algorithm to solve the maze.
 * In AI, a model is trained by feeding it a lot of data so that the model trains everytime it
 * encounters new conditions or data and learns from it. This is called training the model.
 * The function studentAI implements a model which is trained over multiple iterations and finally
 * when the model is trained it solves the maze just like a human would do.
 *
 * Model - at each cell of the maze, the model tries to traverse in this order - L, R, F. As in,
 * model evaluates if left is allowed, it would take left. If Left is not allowed, it will try to
 * traverse right if allowed. Lastly it would try to traverse forward.
 *
 * There are following conditions which may prevent traversal in a given direction -
 * 1. There is a wall - this can be checked by the functions already provided in micromouse class
 * OR
 * 2. The cell has already been visited - every time the nouse visits a cell, it marks it as visited
 *
 * Training the model - When the model takes a L or R, it records the last decision it took - x,y & dir
 * of traversal. If the mouse gets stuck, the model learns that it's last decision was not correct. For
 * this it updates a database and marks the direction taken at last decision to be not allowed at the
 * last decision x & y co-ordinates. Once database is updated, the model starts traversing the maze
 * from the begining. In this way, whenever the mouse is stuck, the model reverts only the last decision
 * and starts all over again.
 *
 * What does stuck mean - A mouse is considered stuck if it has entered a cell which has walls on all side
 * or it has already visited the cells in the allowed directions (this condition is to prevent the model
 * from going into a loop)
 */
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

    QPoint newPos;
    static int last_decision_x = 0;
    static int last_decision_y = 0;
    static Direction last_decision_direction = F;
    static int last_turn = 0;

    if ((isWallLeftEnhanced() == false) &&
            (checkDatabaseForDecision(findxPos(),findyPos(),L) == true))
    {
        last_decision_x = findxPos();
        last_decision_y = findyPos();
        last_decision_direction = L;
        isVisited[findxPos()][findyPos()] = 1;
        turnLeft();
        moveForward();
        if(last_turn) last_turn++;
        else last_turn = 0;

        cout << "take left " << last_decision_x << " " << last_decision_y << " " << last_decision_direction << endl ;
    }
    else if ((isWallRightEnhanced() == false) &&
             (checkDatabaseForDecision(findxPos(),findyPos(),R) == true))
    {
        last_decision_x = findxPos();
        last_decision_y = findyPos();
        last_decision_direction = R;
        isVisited[findxPos()][findyPos()] = 1;
        turnRight();
        moveForward();
        if(last_turn == 0) last_turn++;
        else last_turn = 0;

        cout << "take right " << last_decision_x << " " << last_decision_y << " " << last_decision_direction << endl;
    }
    else if ((isWallForwardEnhanced() == false) &&
             (checkDatabaseForDecision(findxPos(),findyPos(),F) == true))
    {
        moveForward();
        last_turn = 0;
    }
    //If none of those conditions are carried out, then mouse is either stuck or in loop
    else
    {
        //If mouse has done R->L->L and closingCondition returns true, then finish
        if(closingCondition(last_turn) == true)
        {
            cout << "Model is trained now !!!" << endl;
            foundFinish();
            printUI("Reached destination");
        }
        else
        {
            cout << "mouse stuck at "<< findxPos() << " " << findyPos() << endl;
            updateDatabase(last_decision_x,last_decision_y,last_decision_direction);
        }
        newPos.setX(1);
        newPos.setY(1);
        this->maze->drawMouse(newPos, dUP);
        memset(isVisited,0,sizeof(int)*(MAZE_WIDTH+1)*(MAZE_HEIGHT+1));
    }

}
