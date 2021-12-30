#ifndef SERVERIP_H
#define SERVERIP_H
#include "base/inputkvs.h"

class ServerIP : public InputKVs
{
public:
    ServerIP();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);

private:

};

#endif // SERVERIP_H
