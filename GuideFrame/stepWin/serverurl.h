#ifndef SERVERURL_H
#define SERVERURL_H
#include "base/inputkvs.h"
class ServerUrl : public InputKVs
{

public:
    explicit ServerUrl();
    int GetInput(QVariantList& retval);
    int SetInput(QVariantList& retval);

private:

};

#endif // SERVERURL_H
