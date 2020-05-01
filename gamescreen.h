#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLCDNumber>
#include "gameview.h"
#include <QLCDNumber>
#include <QPushButton>
#include <QLabel>
class GameScreen : public QWidget
{
    Q_OBJECT
private:
    int MARGIN;
    QVBoxLayout *mainLayout;
    QVBoxLayout *sideLayout;
    QHBoxLayout *controlLayout;
    QHBoxLayout *buttonLayout;
    QFrame *sideFrame;
    GameView *view;
    QLabel *pointView;
    QPushButton *pauseButton;
    QPushButton *homeButton;
    QPushButton *leftArrow;
    QPushButton *rightArrow;
    QPushButton *downArrow;
    QPushButton *rotateArrow;


public:
    explicit GameScreen(QSize wSize,QWidget *parent = nullptr);
protected:
    void layoutUI();
    void styleUI();
    void connectSignalsAndSlots();
signals:
    void sigGameOver();
    void sigPauseGame();
    void sigHome();
    void sigLeft();
    void sigRight();
    void sigRotate();
    void sigDown();
public slots:
   void slotInit();
   void slotUpdatePoint(int point);
   void slotStopGame();
   void slotNewGame();
   void slotStartGame();
   void slotPauseGame();
   void slotGoHome();
};

#endif // GAMESCREEN_H
