#ifndef TESTTHREADTYPE1_H
#define TESTTHREADTYPE1_H

#include <QThread>

class TestThreadType1 : public QThread
{
    Q_OBJECT
public:
    explicit TestThreadType1(QObject *parent = 0);
    void stop();

protected:
    void run();

signals:

public slots:

private:
    bool _isRuning;
};

#endif // TESTTHREADTYPE1_H
