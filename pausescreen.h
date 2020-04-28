#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
class PauseScreen:public QFrame
{
    Q_OBJECT
private:
    int MARGIN;
    QLabel *title;
    QPushButton *exitButton;
    QPushButton *resumeButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
public:

    PauseScreen(QSize wSize,QWidget *parent=nullptr);
protected:
    void connectSignalsAndSlots();
    void layoutUI();
    void styleUI();
signals:
    void sigNewGame();
    void sigResume();
public slots:
    void slotInit();


};

#endif // PAUSESCREEN_H
