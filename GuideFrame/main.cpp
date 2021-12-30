#include "mainwindow.h"
#include "guideframe.h"
#include "guideconf.h"
#include <unistd.h>
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
#if 0
    for (int i=0;i<1000;i++)
    {
        GuideConf* g = new GuideConf;
        g->show();
        sleep(10);
        delete g;
    }
#endif
    GuideConf* g = new GuideConf;
    g->show();

    return a.exec();
}
