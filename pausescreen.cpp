#include "pausescreen.h"
#include <QGraphicsBlurEffect>
PauseScreen::PauseScreen(QSize wSize, QWidget *parent)
{
    setWindowFlags(Qt::FramelessWindowHint);

    setFixedSize(wSize);
    slotInit();
    layoutUI();
    styleUI();
    connectSignalsAndSlots();

}
void PauseScreen::connectSignalsAndSlots()
{
    connect(exitButton,&QPushButton::clicked,this,&PauseScreen::sigNewGame);
    connect(resumeButton,&QPushButton::clicked,this,&PauseScreen::sigResume);
}

void PauseScreen::layoutUI()
{
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(MARGIN);
    buttonLayout->setMargin(0);
    buttonLayout->setSpacing(MARGIN);
    setLayout(mainLayout);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(resumeButton);
    mainLayout->addLayout(buttonLayout);
    title->move(size().width()/2-title->width()/2,size().height()/6);

}

void PauseScreen::styleUI()
{
}

void PauseScreen::slotInit()
{
    MARGIN=10;
    title = new QLabel("Game Paused",this);
    title->setFixedSize(size().width(),size().height()/6);

    title->setAlignment(Qt::AlignCenter);

    exitButton = new QPushButton("\u2302 \n Home");
    resumeButton = new QPushButton("\u25b6 \n Resume");
    mainLayout = new QVBoxLayout;
    buttonLayout = new QHBoxLayout;
    QSize buttonSize(size()/4);
    int length = buttonSize.width() > buttonSize.height()?buttonSize.height():buttonSize.width();
    buttonSize.setWidth(length);
    buttonSize.setHeight(length);
    exitButton->setFixedSize(buttonSize);
    resumeButton->setFixedSize(buttonSize);

}
