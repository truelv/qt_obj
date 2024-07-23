#ifndef __UI_DEFIND_H__
#define __UI_DEFIND_H__

typedef struct {
    int num;
    char* name;
    char* dir;
} PLAT_TYPE;

typedef struct {
    int num;
    char* name;
    char* rootdir;
    char* type;
} DEV_TYPE;
#define CUM_EOF -1

#endif

