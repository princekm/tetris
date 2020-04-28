#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <QObject>

class SoundManager : public QObject
{
    Q_OBJECT
private:
    static SoundManager *sSoundManager;
    explicit SoundManager(QObject *parent = nullptr);
public:
    static SoundManager* getInstance();
    static void init();
signals:
public slots:
    void  slotPlayPoint();
    void  slotPlayButtonPress();
    void  slotPlayGameOver();

};

#endif // SOUNDMANAGER_H
