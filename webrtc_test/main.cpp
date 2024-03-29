#include "mainwindow.h"
#include <QApplication>

#include "rtcmanager.h"
#include "localcamera.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    LocalCamera w;
    w.show();

    //RTCManager rtcclient;
    //rtcclient.ConnectServer("127.0.0.1", 8888, "webrtc_qt");

    return a.exec();
}
