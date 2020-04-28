#include <QApplication>
#include "uimanager.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UIManager *ui= new UIManager;
    ui->start();
    return a.exec();
}
