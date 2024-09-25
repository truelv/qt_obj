#ifndef __UI_DEFIND_H__
#define __UI_DEFIND_H__

typedef struct {
    int num;
    const char* name;
    const char* dir;
    int supflag;    // 支持设备标记
} PLAT_TYPE;

typedef struct {
    int num;
    const char* name;
    const char* rootdir;
    const char* type;
    int devflag;
} DEV_TYPE;

//
typedef enum {
    LT_NONE = 0,
    LT_REPLACE_BIN,
    LT_VIEW_ROUTE,
    LT_VIEW_IP,
    LT_VIEW_DNS,
    LT_REPLACE_ISPCONF,
    LT_KERNEL_UP,
    LT_KERNEL_VER,
} LIST_TYPE;

typedef struct {
    int num;
    const char* name;
    LIST_TYPE type;
} CMD_LIST;
#define CUM_EOF -1

#endif

