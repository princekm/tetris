#ifndef GAMEVIEW_H
#define GAMEVIEW_H
#include <QGraphicsView>
#include "block.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
private:
    int ROWS;
    int COLUMNS;
    int INTERVAL_MILLI_SECS;
    int yMin;
    int points=0;
    Block *matrix[8][16];
    bool isCompleted[16];
    bool isPaused;
    int rowGap;
    int yMax;
    QTimer *timer;
     QStringList colorList;


    QMap <QTimeLine*,Block*> deleteMap;
    QList <Block*>currentList;
public:
    GameView(qreal  width,QWidget *parent=nullptr);
    ~GameView();
protected:
    void init();
    void clearCompleted();
    void clearMatrix(bool del);
    void updateStyle();
    void connectSignalsAndSlots();
    void drawGridLines();
    bool hasNextEmpty(QPoint point);
    bool hasPreviousEmpty(QPoint point);
    bool hasRightEmpty(QPoint point);
    bool isOfCurrentSet(Block *block);
    bool pullBlockDown(Block *block,int times=-1);
    void pullBlocksIterativelyDown(int bottom,int top,int clearedIndices);
    int getRandomBetween(int min,int max);
    QPoint getRandomPoint(QVector <QPoint>);
    QVector <QPoint> getAdjacentBlocks(QPoint p);
    bool canCreateBlockAt(QPoint p);
    bool isRowComplete(int y);
    bool isGameOver();
    int getFirstComplete();
    bool isRotationPossible();
    bool canCurrentSetMove();
    bool canCurrentSetMoveRight();
    bool canCurrentSetMoveLeft();
    void checkAndSetArray();
    void removeBlocksIfArrayIsSet();
    void removeBlocksAt(int y);
    void connectSignalAndSlot(QTimeLine *timer);
    void setMatrixWithCurrent();
    void createBlock(QPoint point,QColor color);
    void rotateCurrentSet();
    void getActiveMatrix(QPoint &topLeft,QPoint &bottomRight);
    int updateYMin();
    void printMatrix();
    void toggleTimer(bool start);
    QPoint getFirstPoint();

Q_SIGNALS:
    void sigGameOver();
    void sigPoint(int points);
    void sigCreateNewSet();
    void sigRotate();
    void sigLeft();
    void sigRight();
    void sigDown();
    void sigBlock();

public Q_SLOTS:
    void slotCreateNewSet();
    void slotAdvanceCurrentSet();
    void slotPullDownCurrentSet();
    void slotMoveLeftCurrentSet();
    void slotMoveRightCurrentSet();
    void slotRefresh();
    void slotDeleteBlock();
    void slotStartGame();
    void slotStopGame();
    void slotPauseGame();
    void slotDownPressed();
    void slotRotatePressed();
    void slotLeftPressed();
    void slotRightPressed();





    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event) override;
};


#endif // GAMEVIEW_H
