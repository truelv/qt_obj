#include "deviceInfo.h"
#include "base/tcpIp/multicast.h"
#include "protocol/device_prot.h"
#include "base/tcpIp/socket_file.h"
#include "base/core/task_core.h"
#include <stdio.h>
#include <QtDebug>
extern TASK_ENTRY* task_entry;
int scanDevice(handMulticastRsp cb) {
    CMD_RSP_INIT(rsp);
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    cmd->base.cmd = CMD_DEVICE_SCAN;

    qDebug() << "执行扫描设备...";
    if (nullptr==cb)
        return -1;
    int ret = multicast_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), sizeof(DEV_CMD),
                                     "224.0.1.0", 10000, cb, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
    }
    qDebug() << "执行扫描设备结束";
    return  0;
}

// 对收到的命令恢复校验
static int rspCheck(char* rspstr, int len) {
    int ret = -1;
    // 验证DEV_CMD_RSP
    DEV_CMD_RSP* rsp = (DEV_CMD_RSP*)rspstr;
    switch (rsp->cmd.base.code) {
    case CMD_RSP_CODE_OK:
    case CMD_RSP_CODE_REDY:
        ret = 0;
        qDebug() << (int)(rsp->cmd.base.cmd) << " 命令成功被接收";
        break;
    default:
        qDebug() << (int)(rsp->cmd.base.cmd) << " 命令接收失败，错误码 " << rsp->cmd.base.code;
        if (-CMD_RSP_CODE_PROT_VER==rsp->cmd.base.code) {
            qDebug() << "协议版本号不一致对方版本号 " << rsp->cmd.base.vMajor<<"."<<rsp->cmd.base.vMinor<<"."<<rsp->cmd.base.vtail;
        }
        break;
    }
    return  ret;
}

typedef struct {
    DEVICE_BASE_INFO* dinfo;
    char file[128];
} DEV_FILE_SEND;
// 读文件，写文件回调
static void send_file(void* arg) {
    DEV_FILE_SEND* sarg = (DEV_FILE_SEND*)arg;
    printf("send file task ip %s, file %s\n", sarg->dinfo->ip, sarg->file);
    ip_send_file(sarg->dinfo->ip, 10002, sarg->file);
    printf("%s file send over\n", sarg->file);
}
static void recv_file(void* arg) {
    DEV_FILE_SEND* sarg = (DEV_FILE_SEND*)arg;
    printf("recv file task ip %s, file %s\n", sarg->dinfo->ip, sarg->file);
    ip_recv_file(sarg->dinfo->ip, 10002, sarg->file);
    printf("%s file recv over\n", sarg->file);
}

int updateDevice(const char *file, DEVICE_BASE_INFO* dinfo)
{
    CMD_RSP_INIT(rsp);
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    cmd->base.cmd = CMD_DEVICE_UPDATE;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), sizeof(DEV_CMD), dinfo->ip, 10000, rspCheck, 100);
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

int getDevlog(const char* path, DEVICE_BASE_INFO *dinfo)
{
    CMD_RSP_INIT(rsp);
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    cmd->base.cmd = CMD_GET_LOGS;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), sizeof(DEV_CMD), dinfo->ip, 10000, rspCheck, 100);
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
    strcat(fucarg->file, ".tar.gz");
    commit_task(task_entry, recv_file, fucarg, TASK_TYPE_QUEUE);
    return  0;
}

int devReboot(DEVICE_BASE_INFO *dinfo)
{
    CMD_RSP_INIT(rsp);
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    cmd->base.cmd = CMD_DEV_REBOOT;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), sizeof(DEV_CMD), dinfo->ip, 10000, rspCheck, 100);
    if (ret<0) {
        qDebug() << "发送失败, 错误码 " << ret;
        return -1;
    }
    return  0;
}

int upServer(const char *file, DEVICE_BASE_INFO *dinfo)
{
    CMD_RSP_INIT(rsp);
    DEV_CMD* cmd = (DEV_CMD*)&rsp;
    cmd->base.cmd = CMD_SERVER_UP;

    qDebug() << "发送udp地址 " << dinfo->ip;
    int ret = udp_sendmsg_wait((char*)cmd, sizeof(DEV_CMD_RSP), sizeof(DEV_CMD), dinfo->ip, 10000, rspCheck, 100);
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
