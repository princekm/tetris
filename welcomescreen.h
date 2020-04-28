#ifndef WELCOMESCREEN_H
#define WELCOMESCREEN_H
#include <QFrame>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class WelcomeScreen : public QFrame
{
    Q_OBJECT
private:
    int MARGIN;
    QLabel *title;
    QPushButton *exitButton;
    QPushButton *newButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
public:
    WelcomeScreen(QSize wSize,QWidget *parent=nullptr);
protected:
    void connectSignalsAndSlots();
    void layoutUI();
    void styleUI();
signals:
    void sigExit();
    void sigNewGame();
public slots:
    void slotInit();
};

#endif // WELCOMESCREEN_H
