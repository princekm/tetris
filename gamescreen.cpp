#include "gamescreen.h"
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
    mainLayout->addWidget(view);
    mainLayout->addWidget(sideFrame);
    sideLayout->setMargin(0);
    sideLayout->setSpacing(MARGIN);
    sideFrame->setLayout(sideLayout);
    sideLayout->addWidget(pointView);
    sideLayout->addWidget(pauseButton);
    sideLayout->addWidget(homeButton);

    sideFrame->setFixedSize(width()-view->width()-3*MARGIN,height()-2*MARGIN);
    pointView->setFrameStyle(QFrame::Plain);

    QSize buttonSize(size()/4);
    int length = buttonSize.width() > buttonSize.height()?buttonSize.height():buttonSize.width();
    buttonSize.setWidth(length);
    buttonSize.setHeight(length);
    pauseButton->setFixedSize(buttonSize);
    homeButton->setFixedSize(buttonSize);
    pointView ->setFixedSize(buttonSize);
}

void GameScreen::styleUI()
{

//     sideFrame->setStyleSheet("background:#22a6b3");

}

void GameScreen::connectSignalsAndSlots()
{
    connect(view,&GameView::sigPoint,this,&GameScreen::slotUpdatePoint);
    connect(pauseButton,&QPushButton::clicked,this,&GameScreen::slotPauseGame);
    connect(homeButton,&QPushButton::clicked,this,&GameScreen::slotGoHome);
    connect(view,&GameView::sigGameOver,this,&GameScreen::sigGameOver);

}

void GameScreen::slotInit()
{
    view= new GameView (256);
    sideFrame = new QFrame;
    pointView = new QLabel("Score:\n0");
    pointView->setAlignment(Qt::AlignCenter);
    pointView->setObjectName("pointview");

    pauseButton = new QPushButton("\u2016 \nPause");
    homeButton = new QPushButton("\u2302 \n Home");
    MARGIN=10;
    mainLayout = new QHBoxLayout;
    sideLayout = new QVBoxLayout;
}

void GameScreen::slotUpdatePoint(int point)
{
    qDebug()<<point;
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
