#include "gamescreen.h"
#include "soundmanager.h"
#include <QDebug>
GameScreen::GameScreen(QSize wSize, QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(wSize);
    slotInit();
    layoutUI();
    styleUI();
    connectSignalsAndSlots();
}

void GameScreen::layoutUI()
{
    setLayout(mainLayout);
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(MARGIN);
    mainLayout->addWidget(view,1,Qt::AlignCenter);
    mainLayout->addWidget(sideFrame,1,Qt::AlignCenter);
    sideLayout->setMargin(0);
    sideLayout->setSpacing(MARGIN);
    sideFrame->setLayout(sideLayout);
    controlLayout->addWidget(leftArrow);
    controlLayout->addWidget(rotateArrow);
    controlLayout->addWidget(downArrow);
    controlLayout->addWidget(rightArrow);
    buttonLayout->addWidget(pointView);
    buttonLayout->addWidget(pauseButton);
    buttonLayout->addWidget(homeButton);
    controlLayout->setSpacing(MARGIN);
    controlLayout->setMargin(0);
    buttonLayout->setSpacing(MARGIN);
    buttonLayout->setMargin(0);
    sideLayout->addLayout(controlLayout);
    sideLayout->addLayout(buttonLayout);

    pointView->setFrameStyle(QFrame::Plain);

    int buttonLength= (sideFrame->height()-MARGIN)/2.0*0.4;
    QSize buttonSize(buttonLength,buttonLength);
//    pauseButton->setFixedSize(buttonSize);
//    homeButton->setFixedSize(buttonSize);
//    pointView ->setFixedSize(buttonSize);
//    leftArrow->setFixedSize(buttonSize);
//    rightArrow->setFixedSize(buttonSize);
//    rotateArrow ->setFixedSize(buttonSize);
//    downArrow ->setFixedSize(buttonSize);
}

void GameScreen::styleUI()
{


}

void GameScreen::connectSignalsAndSlots()
{
    connect(view,&GameView::sigPoint,SoundManager::getInstance(),&SoundManager::slotPlayPoint);
    connect(view,&GameView::sigPoint,this,&GameScreen::slotUpdatePoint);
    connect(pauseButton,&QPushButton::clicked,this,&GameScreen::slotPauseGame);
    connect(homeButton,&QPushButton::clicked,this,&GameScreen::slotGoHome);
    connect(view,&GameView::sigGameOver,this,&GameScreen::sigGameOver);
    connect(view,&GameView::sigGameOver,SoundManager::getInstance(),&SoundManager::slotPlayGameOver);
    connect(pauseButton,&QPushButton::clicked,SoundManager::getInstance(),&SoundManager::slotPlayButtonPress);
    connect(homeButton,&QPushButton::clicked,SoundManager::getInstance(),&SoundManager::slotPlayButtonPress);

    connect(leftArrow,&QPushButton::clicked,this,&GameScreen::sigLeft);
    connect(rightArrow,&QPushButton::clicked,this,&GameScreen::sigRight);
    connect(rotateArrow,&QPushButton::clicked,this,&GameScreen::sigRotate);
    connect(downArrow,&QPushButton::clicked,this,&GameScreen::sigDown);
    connect(this,&GameScreen::sigLeft,view,&GameView::slotLeftPressed);
    connect(this,&GameScreen::sigRight,view,&GameView::slotRightPressed);
    connect(this,&GameScreen::sigRotate,view,&GameView::slotRotatePressed);
    connect(this,&GameScreen::sigDown,view,&GameView::slotDownPressed);

}

void GameScreen::slotInit()
{
    MARGIN=50;
    int length =size().height()*.2-3*MARGIN;
    sideFrame = new QFrame;
    sideFrame->setFixedSize(size().width()-2*MARGIN,length*2+MARGIN);
    view= new GameView ((size().height()-sideFrame->height())/2);
    pointView = new QLabel("Score:\n0");
    pointView->setAlignment(Qt::AlignCenter);
    pointView->setObjectName("pointview");


    pauseButton = new QPushButton("\u23f8 \nPause");
    homeButton = new QPushButton("🏠 \n Home");
    rightArrow = new QPushButton("\u27a1 \n Right");
    leftArrow = new QPushButton("\u2b05 \n Left");
    rotateArrow = new QPushButton("🔄 \nRotate");
    downArrow = new QPushButton("\u2b07 \nDown");
    mainLayout = new QVBoxLayout;
    sideLayout = new QVBoxLayout;
    controlLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;

}

void GameScreen::slotUpdatePoint(int point)
{
    pointView->setText("Score:\n"+QString::number(point));
}

void GameScreen::slotStopGame()
{
    view->slotStopGame();
}

void GameScreen::slotNewGame()
{
    view->slotStopGame();

    view->slotStartGame();

}

void GameScreen::slotStartGame()
{
    view->slotStartGame();
}

void GameScreen::slotPauseGame()
{
    view->slotPauseGame();
    emit sigPauseGame();
}

void GameScreen::slotGoHome()
{
    slotStopGame();
    emit sigHome();
}
