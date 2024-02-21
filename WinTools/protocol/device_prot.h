#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    char sn[16];
    char ip[20];
} DEVICE_INFO;
int paser_device_info(const char* rsp, DEVICE_INFO* deviceinfo);

#ifdef __cplusplus
}
#endif
