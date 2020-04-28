#include "welcomescreen.h"
#include "QGraphicsBlurEffect"
WelcomeScreen::WelcomeScreen(QSize wSize, QWidget *parent)
{
   // setWindowFlags(Qt::FramelessWindowHint);
    setFixedSize(wSize);
    slotInit();
    layoutUI();
    styleUI();
    connectSignalsAndSlots();
}
void WelcomeScreen::connectSignalsAndSlots()
{
    connect(exitButton,&QPushButton::clicked,this,&WelcomeScreen::sigExit);
    connect(newButton,&QPushButton::clicked,this,&WelcomeScreen::sigNewGame);
}

void WelcomeScreen::layoutUI()
{
    mainLayout->setMargin(MARGIN);
    mainLayout->setSpacing(MARGIN);
    buttonLayout->setMargin(0);
    buttonLayout->setSpacing(MARGIN);
    setLayout(mainLayout);
    buttonLayout->addWidget(exitButton);
    buttonLayout->addWidget(newButton);
    mainLayout->addLayout(buttonLayout);
    title->move(size().width()/2-title->width()/2,size().height()/6);
}

void WelcomeScreen::styleUI()
{
//    setStyleSheet("WelcomeScreen{background:#22a6b3}QPushButton{font-weight:bold;font-size:19pt;background:#2980b9;color:white;border-radius:"+QString::number(exitButton->width()*.3)+"px}");
//    title->setStyleSheet("background:6ab04c;color:white;font-weight:bold;font-size:34pt");
}

void WelcomeScreen::slotInit()
{
    MARGIN=10;
    title = new QLabel("Tetris",this);
    title->setAlignment(Qt::AlignCenter);
    title->setFixedSize(size().width()/2,size().height()/6);


    QString exitString(QChar(0x232b));
    exitString.append("\nExit");
    exitButton = new QPushButton(exitString);
    QString newString;//(QChar(''));
    newString.append("\u25b6 \n New");
    newButton = new QPushButton(newString);
    mainLayout = new QVBoxLayout;
    buttonLayout = new QHBoxLayout;
    QSize buttonSize(size()/4);
    int length = buttonSize.width() > buttonSize.height()?buttonSize.height():buttonSize.width();
    buttonSize.setWidth(length);
    buttonSize.setHeight(length);
    exitButton->setFixedSize(buttonSize);
    newButton->setFixedSize(buttonSize);



}
