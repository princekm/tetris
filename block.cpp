#include "block.h"
#include <QBrush>
#include <QPen>
#include <QPainter>
#include <QVariant>
Block::Block(QPoint point, QSize size,QColor color):QGraphicsRectItem(QRectF(0,0,size.width(),size.height()))
{
    this->point=point;
    MARGIN = 2;
    rectF.setRect(0,0,size.width(),size.height());
    int offset=rectF.width();
    setPos(point.x()*offset,point.y()*offset);
    setBrush(QBrush(color));
    QPen pen(QColor("#ffffff"));
    pen.setWidth(3);
    setPen(pen);
    timer=nullptr;
    animation=nullptr;

}

Block::~Block()
{
    delete animation;
    delete timer;
}

const QPoint &Block::currPos()
{
    return point;
}

void Block::explode()
{

    setBrush(QBrush("#ffffff"));
    setPen(QPen(QColor("#ffffff")));

    timer  = new QTimeLine(100);
    timer->setFrameRange(0, 10);

    animation = new QGraphicsItemAnimation;
    animation->setItem(this);
    animation->setTimeLine(timer);

    for (int i = 200; i > 0; i--)
    {
        animation->setScaleAt(i / 200.0,i/200.0,i/200.0);
    }

    timer->start();

}

QTimeLine *Block::getTimer()
{
    return timer;
}

void Block::setCurrPos(QPoint point)
{
    int offset=rectF.width();
    this->point=point;
    setPos(point.x()*offset,point.y()*offset);

}

void Block::advanceDown()
{
    int offset=rectF.width();
    point.setY(point.y()+1);
    setPos(point.x()*offset,point.y()*offset);
}

void Block::advanceLeft()
{
    int offset=rectF.width();
    point.setX(point.x()-1);
    setPos(point.x()*offset,point.y()*offset);
}

void Block::advanceRight()
{
    int offset=rectF.width();
    point.setX(point.x()+1);
    setPos(point.x()*offset,point.y()*offset);
}

void Block::advanceUp()
{
    int offset=rectF.width();
    point.setY(point.y()-1);
    setPos(point.x()*offset,point.y()*offset);

}



QRectF Block::boundingRect() const
{
    return rectF;
}

void Block::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(brush());
    painter->setPen(pen());
    painter->setRenderHint(QPainter::Antialiasing);
    QRectF f(rectF);
    f.setX(MARGIN);
    f.setY(MARGIN);
    f.setWidth(rectF.width()-2*MARGIN);
    f.setHeight(rectF.height()-2*MARGIN);
    painter->drawRoundedRect(f,rectF.width()/10,rectF.width()/10);
}


void Block::moveDown(int phase)
{

}
