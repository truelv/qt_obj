#ifndef DOORANDCONTRLNUM_H
#define DOORANDCONTRLNUM_H
#include "base/inputkvs.h"

class DoorAndContrlNum : public InputKVs
{
public:
    DoorAndContrlNum();
    int GetInput(QVariantList& retval);
};

#endif // DOORANDCONTRLNUM_H
