#ifndef IFACECHILDOPT
#define IFACECHILDOPT
#include <QVariant>
#include <QDebug>
class IfaceChildOpt {
public:
    IfaceChildOpt() {}
    virtual ~IfaceChildOpt() {}
    // 控件实现GetInput方法带回输入的内容
    virtual int GetInput(QVariantList& retval) = 0;
};

#endif // IFACECHILDOPT

