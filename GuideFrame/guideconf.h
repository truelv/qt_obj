/**
 * 使用组件的示例
*/
#ifndef GUIDECONF_H
#define GUIDECONF_H
#include "guideframe.h"

class GuideConf : public GuideFrame
{
public:
    GuideConf();

    void ReturnPageInput(int index);
};

#endif // GUIDECONF_H
