#include <QApplication>
#include "uimanager.h"
#include "soundmanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SoundManager::init();
    UIManager *ui= new UIManager;
    ui->start();
    return a.exec();
}
