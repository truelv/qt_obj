#include "deviceInfo.h"
#include "base/tcpIp/multicast.h"
#include <stdio.h>
#include <QtDebug>

int scanDevice(handMulticastRsp cb) {
    char sendbuff[64] = "{"
                            "\"cmdgroup\":\"\","
                            "\"cmd\":\"\","
                            // getinfo  base
                            "\"arg1\":\"\""
                            "}";
    qDebug() << "执行扫描设备...";
    if (nullptr==cb)
        return -1;
    int ret = multicast_sendmsg_wait(sendbuff, strlen(sendbuff)+1, "224.0.1.0", 10000, cb, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
    }
    qDebug() << "执行扫描设备结束";
    return  0;
}

// 所有命令的第一包为命令以及参数
// 第二包开始为长数据
int updateDevice(const char *file)
{
    return  0;
}

int getLogs()
{
    return  0;
}
