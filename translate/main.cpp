#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator m;
    m.load(":/Japanese.qm");
    qApp->installTranslator(&m);
    MainWindow w;
    w.show();

    return a.exec();
}
