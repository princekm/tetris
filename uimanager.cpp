#include "uimanager.h"
#include <QApplication>
#include <QGraphicsBlurEffect>
#include <QDialog>
#include <QFile>
UIManager::UIManager(QObject *parent) : QObject(parent)
{
    slotInit();
    layoutUI();
    styleUI();
    connectSignalsAndSlots();
    slotHideAll();
}

void UIManager::start()
{
    container->show();
    emit sigShowWelcomeScreen();
}

void UIManager::connectSignalsAndSlots()
{

    connect(this,&UIManager::sigShowWelcomeScreen,this,&UIManager::slotShowWelcomeScreen);
    connect(gameScreen,&GameScreen::sigGameOver,this,&UIManager::slotShowGameOverScreen);
    connect(gameScreen,&GameScreen::sigPauseGame,this,&UIManager::slotShowPauseScreen);

    connect(gameScreen,&GameScreen::sigHome,gameScreen,&GameScreen::slotStopGame);
    connect(gameScreen,&GameScreen::sigHome,this,&UIManager::slotShowWelcomeScreen);

    connect(pauseScreen,&PauseScreen::sigResume,this,&UIManager::slotShowGameScreen);
    connect(pauseScreen,&PauseScreen::sigResume,gameScreen,&GameScreen::slotStartGame);

    connect(pauseScreen,&PauseScreen::sigNewGame,gameScreen,&GameScreen::slotStartGame);
    connect(pauseScreen,&PauseScreen::sigNewGame,this,&UIManager::slotShowGameScreen);


    connect(welcomeScreen,&WelcomeScreen::sigNewGame,gameScreen,&GameScreen::slotNewGame);
    connect(welcomeScreen,&WelcomeScreen::sigNewGame,this,&UIManager::slotShowGameScreen);


    connect(welcomeScreen,&WelcomeScreen::sigExit,this,&QApplication::quit);

    connect(gameOverScreen,&GameOverScreen::sigGoBack,this,&UIManager::slotShowWelcomeScreen);
    connect(gameOverScreen,&GameOverScreen::sigRestart,gameScreen,&GameScreen::slotStartGame);
    connect(gameOverScreen,&GameOverScreen::sigRestart,this,&UIManager::slotShowGameScreen);


}

void UIManager::layoutUI()
{

    container->setLayout(mainLayout);
    mainLayout->addWidget(gameScreen);
    mainLayout->addWidget(welcomeScreen);
    mainLayout->addWidget(pauseScreen);
    mainLayout->addWidget(gameOverScreen);

}

void UIManager::styleUI()
{
    QFile File("://styles/style.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    qApp->setStyleSheet(StyleSheet);

}

void UIManager::slotInit()
{
    QSize wSize(384,532);
    container = new QFrame();
    container->setWindowFlags(Qt::FramelessWindowHint);
    container->setFixedSize(wSize);


    QSize dialogSize(wSize/2);
    gameScreen = new GameScreen(wSize);
    pauseScreen = new PauseScreen(wSize);
    gameOverScreen =new GameOverScreen(wSize);
    welcomeScreen = new WelcomeScreen(wSize);
    mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    currentScreen=gameScreen;
}

void UIManager::slotShowGameOverScreen()
{
    currentScreen->hide();
    gameOverScreen->show();
    currentScreen=gameOverScreen;
}

void UIManager::slotShowWelcomeScreen()
{
    currentScreen->hide();
    welcomeScreen->show();
    currentScreen=welcomeScreen;
}

void UIManager::slotShowPauseScreen()
{
    currentScreen->hide();
    pauseScreen->show();
    currentScreen=pauseScreen;

}

void UIManager::slotShowGameScreen()
{
    currentScreen->hide();
    gameScreen->show();
    currentScreen=gameScreen;

}

void UIManager::slotHideAll()
{
    gameOverScreen->hide();
    gameScreen->hide();
    pauseScreen->hide();
    welcomeScreen->hide();
}
