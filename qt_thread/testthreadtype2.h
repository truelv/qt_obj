#ifndef TESTTHREADTYPE2_H
#define TESTTHREADTYPE2_H

#include <QObject>

class TestThreadType2 : public QObject
{
    Q_OBJECT
public:
    explicit TestThreadType2(QObject *parent = 0);
    ~TestThreadType2();

signals:

protected slots:
    void doWork();

public slots:
    void stop();

private:
    bool _isruning;
};

#endif // TESTTHREADTYPE2_H
