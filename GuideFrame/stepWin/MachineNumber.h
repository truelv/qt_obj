#ifndef MACHINENUMBER_H
#define MACHINENUMBER_H
#include "base/inputkvs.h"

class MachineNumber: public InputKVs
{
public:
    MachineNumber();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);
};

#endif // MACHINENUMBER_H
