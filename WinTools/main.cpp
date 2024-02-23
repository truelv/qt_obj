#include "mainwindow.h"
#include "base/tcpIp/multicast.h"
#include "base/core/task_core.h"
#include <stdio.h>
#include <QApplication>
#include <QTextCodec>

TASK_ENTRY* task_entry = NULL;

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf-8"));
    setbuf(stdout, NULL);
    printf("build time %s\n", __TIME__);
    QApplication a(argc, argv);
    MainWindow w;
    int ret = start_task_core(&task_entry, 2);
    if (ret<0) {
        printf("start task core errro, ret %d\n", ret);
    }
    w.show();
    return a.exec();
}
