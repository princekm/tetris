#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
class GameOverScreen : public QFrame
{
    Q_OBJECT
private:
    int MARGIN;
    QLabel *title;
    QPushButton *backButton;
    QPushButton *restartButton;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
public:
    GameOverScreen(QSize wSize,QWidget *parent=nullptr);
protected:
    void connectSignalsAndSlots();
    void layoutUI();
    void styleUI();
signals:
    void sigGoBack();
    void sigRestart();
public slots:
    void slotInit();
};

#endif // GAMEOVERSCREEN_H
