#ifndef __UI_DEFIND_H__
#define __UI_DEFIND_H__

// int 32bit 高位2字节平台类型，地位2字节设备类型,总共可以表示16x16个设备
#define SUP_PLAT_YT     0x010000
#define SUP_PLAT_YTH    0x020000
#define SUP_PLAT_ETC    0x040000
#define SUP_PLAT_40     0x080000
#define SUP_PLAT_ACS    0x100000
// 平台类型
typedef struct {
    int num;
    const char* name;
    const char* dir;    // 应用工程名称，前缀
    int supflag;    // 支持设备标记
    int platfalg;   // 平台类型标记
} PLAT_TYPE;

// 设备类型
// devflag
#define SUP_DEV_DCTR_YT328      0x01
#define SUP_DEV_DCTR_YT327L     0x02
#define SUP_DEV_READER_YT328    0x04
#define SUP_DEV_CONTRL_YT312    0x08
#define SUP_DEV_TK_YT312        0x10
#define SUP_DEV_YT213           0x20
#define SUP_DEV_YT215           0x40
#define SUP_DEV_YT216           0x80

typedef struct {
    int num;
    const char* name;
    const char* rootdir;    // 设备工程根目录
    const char* type;       // 应用工程名称，后缀
    int devflag;        // 设备类型标记
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

// 执行命令结构体
typedef struct {
    int num;
    const char* name;
    LIST_TYPE type;
} CMD_LIST;
#define CUM_EOF -1

#endif

