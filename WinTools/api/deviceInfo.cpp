#include "deviceInfo.h"
#include "base/tcpIp/multicast.h"
#include "protocol/device_prot.h"
#include "base/tcpIp/socket_file.h"
#include "base/core/task_core.h"
#include <stdio.h>
#include <QtDebug>
extern TASK_ENTRY* task_entry;
int scanDevice(handMulticastRsp cb) {
    DEVICE_INFO info;
    DEV_CMD* cmd = (DEV_CMD*)&info;
    memset(cmd, 0, sizeof(DEV_CMD));
    cmd->cmd = CMD_DEVICE_SCAN;

    qDebug() << "执行扫描设备...";
    if (nullptr==cb)
        return -1;
    int ret = multicast_sendmsg_wait((char*)cmd, sizeof(DEVICE_INFO), "224.0.1.0", 10000, cb, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
    }
    qDebug() << "执行扫描设备结束";
    return  0;
}

//
static int rspCheck(char* rspstr, int len) {
    int ret = -1;
    // 验证DEV_CMD_RSP
    DEV_CMD_RSP* rsp = (DEV_CMD_RSP*)rspstr;
    switch (rsp->code) {
    case CMD_RSP_CODE_OK:
    case CMD_RSP_CODE_REDY:
        ret = 0;
        qDebug() << (int)(rsp->cmd.cmd) << " 命令成功被接收";
        break;
    default:
        break;
    }
    return  ret;
}

typedef struct {
    DEVICE_INFO* dinfo;
    char file[128];
} DEV_FILE_SEND;
static void send_file(void* arg) {
    DEV_FILE_SEND* sarg = (DEV_FILE_SEND*)arg;
    printf("send file task ip %s, file %s\n", sarg->dinfo->ip, sarg->file);
    ip_send_file(sarg->dinfo->ip, 10002, sarg->file);
    // 需要回收参数
    delete sarg;
}
static void recv_file(void* arg) {
    DEV_FILE_SEND* sarg = (DEV_FILE_SEND*)arg;
    printf("recv file task ip %s, file %s\n", sarg->dinfo->ip, sarg->file);
    ip_recv_file(sarg->dinfo->ip, 10002, sarg->file);
    // 需要回收参数
    delete sarg;
}

int updateDevice(const char *file, DEVICE_INFO* dinfo)
{
    DEV_CMD_RSP rsp;
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    memset(cmd, 0, sizeof(DEV_CMD));
    cmd->cmd = CMD_DEVICE_UPDATE;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), dinfo->ip, 10000, rspCheck, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
        return -1;
    }

    qDebug() << "发送文件 " << file;
    // 如果成功，开始发送文件直到结束
    DEV_FILE_SEND* fucarg = new DEV_FILE_SEND;
    fucarg->dinfo = dinfo;
    memcpy(fucarg->file, file, strlen(file)+1);
    commit_task(task_entry, send_file, fucarg, TASK_TYPE_QUEUE);
    return  0;
}

int getDevlog(const char* path, DEVICE_INFO *dinfo)
{
    DEV_CMD_RSP rsp;
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    memset(cmd, 0, sizeof(DEV_CMD));
    cmd->cmd = CMD_GET_LOGS;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), dinfo->ip, 10000, rspCheck, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
        return -1;
    }

    qDebug() << "接收文件" << path;
    // 如果成功，开始发送文件直到结束
    DEV_FILE_SEND* fucarg = new DEV_FILE_SEND;
    fucarg->dinfo = dinfo;
    memcpy(fucarg->file, path, strlen(path)+1);
    strcat(fucarg->file, "/");
    strcat(fucarg->file, fucarg->dinfo->sn);
    strcat(fucarg->file, ".txt");
    commit_task(task_entry, recv_file, fucarg, TASK_TYPE_QUEUE);
    return  0;
}

int devReboot(DEVICE_INFO *dinfo)
{
    DEV_CMD_RSP rsp;
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    memset(cmd, 0, sizeof(DEV_CMD));
    cmd->cmd = CMD_DEV_REBOOT;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), dinfo->ip, 10000, rspCheck, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
        return -1;
    }
    return  0;
}
