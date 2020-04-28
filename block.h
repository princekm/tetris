#ifndef BLOCK_H
#define BLOCK_H
#include <QGraphicsRectItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>

class Block : public  QGraphicsRectItem
{
private:
    QPoint point;
    QRectF rectF;
    int MARGIN;
    QTimeLine *timer;
    QGraphicsItemAnimation *animation ;
public:
    Block(QPoint point,QSize size,QColor color="#6ab04c");
    ~Block();
    const QPoint& currPos();
    void explode();
    QTimeLine * getTimer();
    void setCurrPos(QPoint point);
    void advanceDown();
    void advanceLeft();
    void advanceRight();
    void advanceUp();


    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // QGraphicsItem interface
public:
    void moveDown(int phase) override;
};


#endif // BLOCK_H
