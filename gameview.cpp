#include "gameview.h"
#include <QDebug>
#include <cstring>
#include <QRandomGenerator>
#include <QTimer>
#include <QKeyEvent>
#include <iostream>
GameView::GameView(int width,QWidget *parent):QGraphicsView(parent)
{
    setFixedWidth(width);
    COLUMNS = 8;
    ROWS = 16;
    INTERVAL_MILLI_SECS=500;
    setFixedHeight(width*2);
    init();
    updateStyle();
    connectSignalsAndSlots();
    drawGridLines();
    sigPoint(0);


}

GameView::~GameView()
{

}

void GameView::init()
{
    colorList.append("#8c7ae6");
    colorList.append("#44bd32");
    colorList.append("#fbc531");
    colorList.append("#0097e6");
    yMin=ROWS;
    yMax=0;
    isPaused=false;
    rowGap=0;
    clearCompleted();
    clearMatrix(false);
    setScene(new QGraphicsScene);
    setContentsMargins(0,0,0,0);
    setSceneRect(contentsRect());
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scene()->setBackgroundBrush(QBrush("#34495e"));
    timer= new QTimer(this);
}

void GameView::clearCompleted()
{
    for(int i=0;i<16;++i)
        isCompleted[i]=false;
}

void GameView::clearMatrix(bool del)
{
    for(int x=0;x<COLUMNS;++x)
    {
        for(int y=0;y<ROWS;++y)
        {
            if(!del)
                matrix[x][y]=nullptr;
            else{
                if(matrix[x][y])
                {
                    scene()->removeItem(matrix[x][y]);
                    delete matrix[x][y];
                    matrix[x][y]=nullptr;
                }
            }
        }
    }

}



void GameView::updateStyle()
{
    setStyleSheet("border:none");
}

void GameView::connectSignalsAndSlots()
{
    connect(timer,&QTimer::timeout,this,&GameView::slotRefresh);
}

void GameView::drawGridLines()
{
    int offset = width()/COLUMNS;
    QPen pen(QColor("#2c3e50"));
    pen.setWidth(1);
    pen.setStyle(Qt::DotLine);
    for(int col=0;col<=COLUMNS;++col)
    {
        QGraphicsLineItem *lineItem= scene()->addLine((col)*offset,0,(col)*offset,height());

        lineItem->setPen(pen);
    }
    for(int row=0;row<=ROWS;++row)
    {
        QGraphicsLineItem *lineItem= scene()->addLine(0,(row)*offset,width(),(row)*offset);
        lineItem->setPen(pen);
    }
}

bool GameView::hasNextEmpty(QPoint point)
{

    bool isValid=true;
    if(point.y()>=-4 && point.y() < ROWS-1)
    {
        if(point.y()>=-4 && point.y()<=-1)
            isValid = true;
        else if(matrix[point.x()][point.y()+1]==nullptr)
        {
            isValid = true;
        }
        else if(matrix[point.x()][point.y()+1]!=nullptr)
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}

bool GameView::hasPreviousEmpty(QPoint point)
{
    bool isValid=true;
    if(point.y()>-4 && point.y() < ROWS)
    {
        if(point.y()>-4 && point.y()<=-1)
            isValid = true;
        else if(matrix[point.x()][point.y()-1]==nullptr)
        {
            isValid = true;
        }
        else if(matrix[point.x()][point.y()-1]!=nullptr)
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}

bool GameView::hasRightEmpty(QPoint point)
{
    bool isValid=true;
    if(point.x()>=0 && point.x() < COLUMNS-1)
    {
        if(matrix[point.x()+1][point.y()]==nullptr)
        {
            isValid = true;
        }
        else if(matrix[point.x()+1][point.y()]!=nullptr)
        {
            isValid = false;
        }
    }
    else
    {
        isValid = false;
    }
    return isValid;
}

bool GameView::isOfCurrentSet(Block *block)
{

    foreach(Block *currBlock,currentList)
    {
        if(currBlock == block)
            return true;
    }
    return false;
}

bool GameView::pullBlockDown(Block *block,int times)
{
    bool pulledDown=false;
    int count=times;

    while(hasNextEmpty(block->currPos())&&(count))
    {
        pulledDown=true;
        QPoint point = block->currPos();
        matrix[point.x()][point.y()]=nullptr;
        block->advanceDown();
        count--;

    }
    QPoint point=block->currPos();
    matrix[point.x()][point.y()]=block;
    return pulledDown;
}


void GameView::pullBlocksIterativelyDown(int bottom, int top, int clearedIndices)
{
    if(bottom < ROWS && top >= 0)
    {
        for(int y=bottom;y>=top;y--)
        {
            for(int x=0;x<COLUMNS;++x)
            {
                Block *block=matrix[x][y];
                if(isOfCurrentSet(block))
                {
                    pullBlockDown(block);
                }
                else if(block)
                {
                    pullBlockDown(block,clearedIndices);
                }
            }
        }
    }
}

int GameView::getRandomBetween(int min, int max)
{
    return (qrand() % ((max + 1) - min) + min);
}

QPoint GameView::getRandomPoint(QVector<QPoint> points)
{
    int arrayIndex= (qrand() % ((points.size())));
    return points.at(arrayIndex);
}


QVector<QPoint> GameView::getAdjacentBlocks(QPoint p)
{
    QVector<QPoint> blocks;
    QPoint left(p.x()-1,p.y());
    QPoint top(p.x(),p.y()-1);
    QPoint right(p.x()+1,p.y());
    QPoint bottom(p.x(),p.y()+1);

    if(canCreateBlockAt(left))
    {
        blocks.append(left);
    }
    if(canCreateBlockAt(top))
    {
        blocks.append(top);
    }
    if(canCreateBlockAt(right))
    {
        blocks.append(right);
    }
    if(canCreateBlockAt(bottom))
    {
        blocks.append(bottom);
    }

    return blocks;


}

bool GameView::canCreateBlockAt(QPoint p)
{
    bool isValid=true;
    if( p.y() < -4 || p.y() > -1 )
        isValid= false;
    else if(p.x() < 0 || p.x() > 7 )
        isValid =false;
    else
    {
        foreach(Block *block,currentList)
        {
            if(block->currPos() == p)
            {
                isValid = false;
                break;
            }
        }
    }
    return isValid;
}

bool GameView::isRowComplete(int y)
{
    bool isComplete=true;
    for(int i=0;i<COLUMNS;++i)
    {
        isComplete&=(matrix[i][y]?true:false);
    }
    return isComplete;
}

bool GameView::isGameOver()
{
    bool gameOver=false;
    foreach(Block *block,currentList)
    {
        QPoint point = block->currPos();
        if(point.y()>=-4 && point.y() <= -1)
        {
            gameOver=true;
            break;
        }
    }
    return gameOver;
}

int GameView::getFirstComplete()
{
    for(int y=ROWS-1;y>=0;y--)
    {
        if(isCompleted[y]){
            return y;
        }
    }
    return -1;
}

bool GameView::isRotationPossible()
{
    bool possible=true;
    if(currentList.isEmpty())
    {
        possible = false;
    }
    else
    {
        QPoint topLeft, bottomRight;
        getActiveMatrix(topLeft,bottomRight);

        int horizontalBlocks=bottomRight.x()-topLeft.x()+1;
        int verticalBlocks = bottomRight.y()-topLeft.y()+1;


        if(horizontalBlocks > verticalBlocks)
        {

            QPoint point(topLeft);
            point.setY(point.y()+horizontalBlocks-2);
            if(hasNextEmpty(point))
                possible=true;
            else
                possible=false;

        }
        else if(verticalBlocks > horizontalBlocks)
        {

            QPoint point(topLeft);
            point.setX(point.x()+verticalBlocks-2);
            if(hasRightEmpty(point))
                possible=true;
            else
                possible=false;

        }
        else
        {
            possible = false;
        }


    }
    return possible;
}

bool GameView::canCurrentSetMove()
{
    bool canMove=true;
    foreach(Block *block,currentList)
    {
        canMove&=hasNextEmpty(block->currPos());
    }
    return canMove;

}

bool GameView::canCurrentSetMoveLeft()
{
    bool canMove=true;
    foreach(Block *block,currentList)
    {
        if((block->currPos().x()>0) )
        {
            if((matrix[block->currPos().x()-1][block->currPos().y()]!=nullptr))
            {
                canMove = false;
                break;
            }
        }
        else
        {
            canMove = false;
            break;
        }
    }
    return canMove;
}

bool GameView::canCurrentSetMoveRight()
{
    bool canMove=true;
    foreach(Block *block,currentList)
    {
        if((block->currPos().x())<7)
        {
            if(matrix[block->currPos().x()+1][block->currPos().y()]!=nullptr)
            {
                canMove = false;
                break;
            }
        }
        else
        {
            canMove = false;
            break;

        }
    }
    return canMove;

}

void GameView::checkAndSetArray()
{
    foreach(Block *block,currentList)
    {
        QPoint point=block->currPos();
        if(isCompleted[point.y()]==false)
        {
            bool completed=true;
            for(int x=0;x<COLUMNS;++x)
            {
                completed &= matrix[x][point.y()]?true:false;
            }
            isCompleted[point.y()]=completed;
        }
    }

}

void GameView::removeBlocksIfArrayIsSet()
{
    int maxIndices=0;
    int maxIndex=-1;
    for(int index=getFirstComplete();index!=-1;index=getFirstComplete())
    {
        removeBlocksAt(index);
        maxIndices+=1;
        maxIndex=index;
    }
    if(maxIndices>0)
    {
        sigPoint(points+=(10*maxIndices));
        rowGap = maxIndices;
        yMax=maxIndex-1;
    }
    else
    {
        rowGap=0;
        yMax=0;
    }

}


void GameView::removeBlocksAt(int y)
{
    if(isCompleted[y])
    {
        for(int x=0;x<COLUMNS;++x)
        {
            Block *block= matrix[x][y];
            matrix[x][y]=nullptr;
            if(block)
            {
                block->explode();
                deleteMap.insert(block->getTimer(),block);
                connectSignalAndSlot(block->getTimer());
            }
        }

    }
    isCompleted[y]=false;
}

void GameView::connectSignalAndSlot(QTimeLine *timer)
{
    connect(timer,&QTimeLine::finished,this,&GameView::slotDeleteBlock);
}

void GameView::setMatrixWithCurrent()
{
    foreach(Block *block,currentList)
    {
        QPoint point = block->currPos();
        matrix[point.x()][point.y()]=block;
    }
}

void GameView::createBlock(QPoint point,QColor color)
{
    int size = width()/COLUMNS;
    Block *block=new Block(QPoint(point),QSize(size,size),QColor(color));
    scene()->addItem(block);
    currentList.append(block);

}

void GameView::rotateCurrentSet()
{
    QPoint topLeft, bottomRight;
    getActiveMatrix(topLeft,bottomRight);
    foreach(Block *block,currentList)
    {
        QPoint point=block->currPos();
        block->setCurrPos(QPoint(topLeft.x()+bottomRight.y()-point.y(),topLeft.y()+point.x()-topLeft.x()));
    }
}

void GameView::getActiveMatrix(QPoint &topLeft, QPoint &bottomRight)
{
    QPoint minXY(COLUMNS,ROWS);
    QPoint maxXY(-1,-5);
    foreach(Block *block,currentList)
    {
        QPoint point(block->currPos());
        if(point.x() < minXY.x())
            minXY.setX(point.x());
        if(point.y() < minXY.y())
            minXY.setY(point.y());
        if(point.x() > maxXY.x())
            maxXY.setX(point.x());
        if(point.y() > maxXY.y() )
            maxXY.setY(point.y());
    }
    topLeft.setX(minXY.x());
    topLeft.setY(minXY.y());
    bottomRight.setX(maxXY.x());
    bottomRight.setY(maxXY.y());

}


int GameView::updateYMin()
{

    foreach(Block *block,currentList)
    {
        QPoint point = block->currPos();
        if(point.y() < this->yMin)
        {
            yMin=point.y();
        }

    }

}

void GameView::printMatrix()
{
    /*    qDebug()<<"matrix";
            for(int x=0;x<16;++x)
            {
                for(int y=0;y<8;++y)
                {
                    QString s=matrix[y][x]?" 1 ":" 0 ";
                    std::cout<<qPrintable(s);
                }
                std::cout<<"\n";
                std::cout.flush();
            }
*/

}

void GameView::toggleTimer(bool start)
{
    if(!start)
    {
        timer->stop();
    }
    else
    {
        timer->start(INTERVAL_MILLI_SECS);
    }
}

QPoint GameView::getFirstPoint()
{
    int xMax=7;
    int xMin=0;
    int yMax=4;
    int yMin=1;
    QVector<QPoint> points;
    QPoint firstPoint;
    int x=getRandomBetween(xMin,xMax);
    int y=getRandomBetween(yMin,yMax);
    firstPoint.setX(x);
    firstPoint.setY(-y);
    return firstPoint;
}



void GameView::slotCreateNewSet()
{
    QPoint firstPoint =getFirstPoint();
    int colorIndex=getRandomBetween(0,colorList.size()-1);
    QColor color(colorList.at(colorIndex));
    createBlock(firstPoint,color);
    QPoint secondPoint=getRandomPoint(getAdjacentBlocks(firstPoint));
    createBlock(secondPoint,color);
    QPoint thirdPoint=getRandomPoint(getAdjacentBlocks(secondPoint));
    createBlock(thirdPoint,color);
    QPoint fourthPoint=getRandomPoint(getAdjacentBlocks(thirdPoint));
    createBlock(fourthPoint,color);

}

void GameView::slotAdvanceCurrentSet()
{
    foreach(Block *block,currentList)
    {
        block->advanceDown();
    }

}

void GameView::slotPullDownCurrentSet()
{

}

void GameView::slotMoveLeftCurrentSet()
{

    foreach(Block *block,currentList)
    {
        block->advanceLeft();
    }

}

void GameView::slotMoveRightCurrentSet()
{

    foreach(Block *block,currentList)
    {
        block->advanceRight();
    }

}

void GameView::slotRefresh()
{

    printMatrix();

    if(rowGap!=0)
    {


        pullBlocksIterativelyDown(yMax,yMin,rowGap);

        yMin+=rowGap;
        updateYMin();

        checkAndSetArray();
        removeBlocksIfArrayIsSet();

        if(rowGap==0)
        {
            currentList.clear();
        }

    }
    else if(currentList.isEmpty())
    {
        slotCreateNewSet();

    }
    else
    {
        bool canMove = canCurrentSetMove();
        if(canMove)
        {

          //  qDebug()<<"advancing";
            slotAdvanceCurrentSet();


        }
        else if(!canMove)
        {

            if(isGameOver())
            {
                //
                emit sigGameOver();
                clearMatrix(true);
                slotStopGame();
            }
            else
            {

            //    qDebug()<<"block settled";
                setMatrixWithCurrent();
                updateYMin();
              //  qDebug()<<"ymin="<<yMin;
                checkAndSetArray();
                removeBlocksIfArrayIsSet();
                if(rowGap==0)
                {
                    currentList.clear();
                }
            }



        }
    }
}

void GameView::slotDeleteBlock()
{

    QTimeLine *sender = qobject_cast<QTimeLine*>(QObject::sender());
    Block *block=deleteMap.value(sender);
    scene()->removeItem(block);
    deleteMap.remove(sender);
    currentList.removeOne(block);
    delete block;
}

void GameView::slotStartGame()
{
    toggleTimer(true);
    isPaused=false;

}

void GameView::slotStopGame()
{
    toggleTimer(false);
    qDebug()<<"stopping timer";

    clearMatrix(true);
    foreach(Block *block,currentList)
    {
        scene()->removeItem(block);
        delete block;
    }
    points=0;
    yMin=ROWS;
    isPaused=false;
    rowGap=0;
    yMax=0;
    currentList.clear();
}

void GameView::slotPauseGame()
{
    toggleTimer(false);
    isPaused=true;
}



void GameView::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key::Key_Up:
        if(isRotationPossible())
            rotateCurrentSet();
        break;
    case Qt::Key::Key_Left:
        if(!isPaused)
            if(canCurrentSetMoveLeft())
                slotMoveLeftCurrentSet();
        break;
    case Qt::Key::Key_Right:
        if(!isPaused)
            if(canCurrentSetMoveRight())
                slotMoveRightCurrentSet();
        break;
    case Qt::Key::Key_Down:
        if(!isPaused)
            if(canCurrentSetMove())
                slotAdvanceCurrentSet();
        break;
    case Qt::Key::Key_P:
        if(!isPaused)
            slotPauseGame();
        else
            slotStartGame();
        break;


    }

    QGraphicsView::keyPressEvent(event);
}
