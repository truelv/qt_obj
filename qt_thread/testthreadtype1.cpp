#include "testthreadtype1.h"
#include <QDebug>
#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#ifdef __cplusplus
}
#endif
TestThreadType1::TestThreadType1(QObject *parent) : QThread(parent),
  _isRuning(false)
{

}

void TestThreadType1::stop()
{
    _isRuning = false;
    //this->quit();
}

void TestThreadType1::run()
{
    _isRuning = true;
    while (_isRuning) {
        qDebug() << "方式一运行线程";
        sleep(1);
    }
}

