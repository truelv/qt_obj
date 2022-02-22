#ifndef DOORANDCONTRLNUM_H
#define DOORANDCONTRLNUM_H
#include "base/inputkvs.h"

class DoorAndContrlNum : public InputKVs
{
    Q_OBJECT
public:
    DoorAndContrlNum();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);

protected slots:
    void  UpperText(QString text);
};

#endif // DOORANDCONTRLNUM_H
