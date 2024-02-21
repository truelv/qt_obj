#pragma once
#ifdef __cplusplus
extern "C" {
#endif
#include "base/tcpIp/multicast.h"
// 扫描设备
int scanDevice(handMulticastRsp cb);
// 更新设备应用程序
// 包文件
int updateDevice(const char* file);
int getLogs();

#ifdef __cplusplus
}
#endif

