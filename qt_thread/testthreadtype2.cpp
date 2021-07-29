#include "testthreadtype2.h"
#include <QDebug>
#include <unistd.h>

TestThreadType2::TestThreadType2(QObject *parent) : QObject(parent)
{
    _isruning = false;
}

TestThreadType2::~TestThreadType2()
{

}

void TestThreadType2::doWork()
{
    _isruning = true;
    while (_isruning) {
        qDebug() << "方式二运行线程";
        sleep(1);
    }

}

void TestThreadType2::stop()
{
    _isruning = false;
}

