#ifndef UIMANAGER_H
#define UIMANAGER_H
#include <QObject>
#include <QHBoxLayout>
#include <QStackedLayout>
#include "gamescreen.h"
#include "pausescreen.h"
#include "gameoverscreen.h"
#include "welcomescreen.h"
class UIManager : public QObject
{
    Q_OBJECT
private:
    QFrame *container;
    QFrame *blurWidget;
    GameScreen *gameScreen;
    WelcomeScreen *welcomeScreen;
    PauseScreen *pauseScreen;
    GameOverScreen *gameOverScreen;
    QHBoxLayout *mainLayout;
    QWidget *currentScreen;

public:
    explicit UIManager(QObject *parent = nullptr);
    void start();
protected:
    void connectSignalsAndSlots();
    void layoutUI();
    void styleUI();
signals:
    void sigShowWelcomeScreen();
public slots:
    void slotInit();
    void slotShowGameOverScreen();
    void slotShowWelcomeScreen();
    void slotShowPauseScreen();
    void slotShowGameScreen();
    void slotHideAll();

};


#endif // UIMANAGER_H
