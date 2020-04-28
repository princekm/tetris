#include "gameoverscreen.h"
#include <QGraphicsBlurEffect>
GameOverScreen::GameOverScreen(QSize wSize, QWidget *parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setFixedSize(wSize);
    slotInit();
    layoutUI();
    styleUI();
    connectSignalsAndSlots();
}

void GameOverScreen::connectSignalsAndSlots()
{
    connect(backButton,&QPushButton::clicked,this,&GameOverScreen::sigGoBack);
    connect(restartButton,&QPushButton::clicked,this,&GameOverScreen::sigRestart);
}

void GameOverScreen::layoutUI()
{
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(MARGIN);
    buttonLayout->setMargin(0);
    buttonLayout->setSpacing(MARGIN);
    setLayout(mainLayout);
    buttonLayout->addWidget(backButton);
    buttonLayout->addWidget(restartButton);
    mainLayout->addLayout(buttonLayout);
    title->move(size().width()/2-title->width()/2,size().height()/6);

}

void GameOverScreen::styleUI()
{

}

void GameOverScreen::slotInit()
{
    MARGIN=10;
    title = new QLabel("Game Over",this);
    title->setFixedSize(size().width()/2,size().height()/6);

    title->setAlignment(Qt::AlignCenter);
    backButton = new QPushButton("\u2302 \n Home");
    restartButton = new QPushButton("\u21ba \n Restart");
    mainLayout = new QVBoxLayout;
    buttonLayout = new QHBoxLayout;
    QSize buttonSize(size()/4);
    int length = buttonSize.width() > buttonSize.height()?buttonSize.height():buttonSize.width();
    buttonSize.setWidth(length);
    buttonSize.setHeight(length);
    backButton->setFixedSize(buttonSize);
    restartButton->setFixedSize(buttonSize);

}
