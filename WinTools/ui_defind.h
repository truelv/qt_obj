#ifndef __UI_DEFIND_H__
#define __UI_DEFIND_H__

typedef struct {
    int num;
    const char* name;
    const char* dir;
} PLAT_TYPE;

typedef struct {
    int num;
    const char* name;
    const char* rootdir;
    const char* type;
} DEV_TYPE;

//
typedef enum {
    LT_NONE = 0,
    LT_REPLACE_BIN,
    LT_VIEW_ROUTE,
    LT_VIEW_IP,
    LT_VIEW_DNS,
} LIST_TYPE;

typedef struct {
    int num;
    const char* name;
    LIST_TYPE type;
} CMD_LIST;
#define CUM_EOF -1

#endif

