#include "soundmanager.h"
#include <QMediaPlayer>
#include <QSound>

SoundManager *SoundManager::sSoundManager=nullptr;

SoundManager::SoundManager(QObject *parent) : QObject(parent)
{

}

SoundManager *SoundManager::getInstance()
{
    if(!sSoundManager)
    {
        sSoundManager = new SoundManager;
    }
    return sSoundManager;
}

void SoundManager::init()
{
    SoundManager::getInstance();
}

void SoundManager::slotPlayPoint()
{
    QSound::play("://music/point.wav");
}

void SoundManager::slotPlayButtonPress()
{
    QSound::play("://music/click.wav");
}

void SoundManager::slotPlayGameOver()
{
    QSound::play("://music/gameover.wav");

}
