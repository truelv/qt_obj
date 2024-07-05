#ifndef SBASE_H
#define SBASE_H
#include <QObject>

class SBase: public QObject
{
    Q_OBJECT
public:
    SBase();
    virtual ~SBase();

    virtual int ServerStart() = 0;
    virtual int ServerStop() = 0;

private:
    QString _name;
};

#endif // SBASE_H
