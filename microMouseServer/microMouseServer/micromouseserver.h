#ifndef MICROMOUSESERVER_H
#define MICROMOUSESERVER_H
#include "mazeConst.h"
#include "mazeBase.h"
#include "mazegui.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QLineF>
#include <QTimer>

enum Direction
{
    L = 0,
    R,
    F
};

namespace Ui {
class microMouseServer;
}

class microMouseServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit microMouseServer(QWidget *parent = 0);
    ~microMouseServer();

private slots:
    void on_tabWidget_tabBarClicked(int index);
    void loadMaze();
    void saveMaze();
    void addLeftWall(QPoint cell);
    void addRightWall(QPoint cell);
    void addTopWall(QPoint cell);
    void addBottomWall(QPoint cell);
    void removeRightWall(QPoint cell);
    void removeLeftWall(QPoint cell);
    void removeTopWall(QPoint cell);
    void removeBottomWall(QPoint cell);
    void netComs();
    void connect2mouse();
    void startAI();
    void studentAI();


private:
    bool isWallLeft();
    bool isWallRight();
    bool isWallForward();
    bool moveForward();
    void turnLeft();
    void turnRight();
    void foundFinish();
    int findxPos(); // Function to find the X coordinate of the mouse
    int findyPos(); // Function to find the Y coordinate of the mouse
    void updateDatabase(int,int,Direction);
    bool checkDatabaseForDecision(int,int,Direction);
    bool closingCondition(int);
    bool isWallLeftEnhanced();
    bool isWallRightEnhanced();
    bool isWallForwardEnhanced();
    void printUI(const char *mesg);

    QTimer *_comTimer;
    QTimer *_aiCallTimer;
    static const int _mDelay = 100;
    Ui::microMouseServer *ui;
    mazeGui *maze;
    std::vector<QGraphicsLineItem*> backgroundGrid;
    struct baseMapNode mazeData[MAZE_WIDTH][MAZE_HEIGHT];
    int dataBase[MAZE_WIDTH+1][MAZE_HEIGHT+1];
    int isVisited[MAZE_WIDTH+1][MAZE_HEIGHT+1];
    void initDatabase();
    void connectSignals();
    void initMaze();
};



#define MAX_DB_ENTRIES 100

#endif // MICROMOUSESERVER_H
