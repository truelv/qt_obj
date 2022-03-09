#include "tcp_server.h"
#include "global.h"
#include "task/face/facedetect_offline.h"

#ifdef __cplusplus
extern "C" {
#endif
#include "base/crc/crc16_xmodem.h"
#include "file_ops.h"
#include "base/utils/mixShell.h"
#ifdef __cplusplus
}
#endif

#undef LOG_TAG
#define LOG_TAG "tcp_server"

// 每个标准包32k
#define DATA_SIZE (32*1024)
#define TMP_LOG_PACKAGE_UPLOAD  PROJECT_DIR_TMP"/log_package.zip"
#define TMP_IMGFACE             PROJECT_DIR_TMP"/face.jpg"

Tcp_Server::Tcp_Server(QThread *parent) :
    QThread(parent),
    _socket(NULL),
    _mode(TCPSERVER_IDEL),
    _readBuffer(NULL),
    _bufferOffset(0),
    _bufferLeft(0),
    _isPacket(false),
    _file(NULL)
{
    // 清空传输信息
    memset(&_transInfo, 0, sizeof(_transInfo));

}

void Tcp_Server::startServer()
{
    _tcpServer.listen(QHostAddress::Any, 10086);
    _tcpServer.setMaxPendingConnections(1);
    connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    _pkg_crc16 = 0;
    //tcp服务开始信号
    emit signalTcpServerStart(true);
}

void Tcp_Server::stopServer()
{
    disconnect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    _pkg_crc16 = 0;
    _tcpServer.disconnect();
    // 清理传输信息
    _mode = TCPSERVER_IDEL;
    memset(&_transInfo, 0, sizeof(_transInfo));
    if (NULL!=_socket)
    {
        _socket->close();
        _socket = NULL;
    }

    resetReadBuffer();
    resetSendFile();

    emit signalTcpServerStart(false);
}

void Tcp_Server::sendAck(const char ackcode)
{
    int len = 0;
    if (NULL==_socket)
        return;

    // 分配ack空间，下面要free掉
    PROTOCOL_SOCKET_ACK* ack = (PROTOCOL_SOCKET_ACK*)calloc(sizeof(PROTOCOL_SOCKET_ACK), 1);
    if (NULL==ack)
    {
        return ;
    }

    ack->head.start_flag = PROTOCOL_TCP_STARTFLAG_ACK;
    ack->head.cmd = _transInfo.cmd;
    len = sizeof(PROTOCOL_SOCKET_ACK);
    *(unsigned short*)(ack->head.lenght) = len;
    ack->reserved.code = ACKCODE_OK;

    // 错误码不同，ack包序号不同
    switch (ackcode)
    {
    case PROTOCOL_SOCKET_ACKCODE_OK_NEXT:
    case PROTOCOL_SOCKET_ACKCODE_OK_OVER:
    case PROTOCOL_SOCKET_ACKCODE_FAILE_AGAIN:
        *(unsigned short*)(ack->pkg_order) = _transInfo.pkg_order+1;
        break;
    case PROTOCOL_SOCKET_ACKCODE_FAILE_INTERUPT:
    case PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE:
        *(unsigned short*)(ack->pkg_order) = 0;
        ack->reserved.code = ACKCODE_ERROR;
        break;
    case PROTOCOL_SOCKET_ACKCODE_OK_CONNECT:
        ack->pkg_order[0] = 1;
        LOG_I("发送ack，成功连接\n");
        break;
    case PROTOCOL_SOCKET_ACKCODE_FAILE_APPTYPE:
        *(unsigned short*)(ack->pkg_order) = 0;
        ack->reserved.code = ACKCODE_ERROR_APPTYPE;
        break;
    case PROTOCOL_SOCKET_ACKCODE_FAILE_APPVER:
        *(unsigned short*)(ack->pkg_order) = 0;
        ack->reserved.code = ACKCODE_ERROR_APPVER;
        break;
    default:
        break;
    }

    //memcpy(ack->soft_version, APP_VERSION, strlen(APP_VERSION)+1);
    // 添加校验
    *(unsigned short*)(ack->crc16) = crc16_xmodem((unsigned char*)ack, len-2);

    LOG_I("ack请求包序号 %d, 回复状态码 %d\n", *(unsigned short*)ack->pkg_order, ack->reserved.code);
    _socket->write((const char*)ack, len);

    // free掉上面的分配内存
    free(ack);
}

void Tcp_Server::sendReq(unsigned short order)
{
    unsigned short pkg_size = 0;
    unsigned short file_size = _file->size();
    char* p_ch = NULL;
    // 超过总包，表示发包完成
    if (order>=(_transInfo.pkg_num))
    {
        // 收到最后一包ack，结束ack
        LOG_I("发包完成，当前包号 %d，总包 %d\n", order, _transInfo.pkg_num);
        resetSendFile();
        // 通知结束
        emit signalTcpReadOver(PROTOCOL_TCPCMD_SENDLOG);
        LOG_I("结束日志发送，进入繁忙\n");
        _mode = TCPSERVER_BUSY;
        //sleep(1);
        LOG_I("结束日志发送，进入空闲\n");
        // 变成空闲
        _mode = TCPSERVER_IDEL;
        return ;
    }
    // 比较上一次发包
    if ((_transInfo.pkg_order+1)!=order)
    {
        // 需要跳包
        _file->seek(order*DATA_SIZE);
    }

    //确认是否是最后一包，最后一包可能不是标准长度
    if (order==(_transInfo.pkg_num-1))
    {
        // 最后一包数据请求ack
        pkg_size = file_size%DATA_SIZE;
    }
    else
    {
        pkg_size = DATA_SIZE;
    }

    // 分配空间
    PROTOCOL_SOCKET_REQUEST *req = (PROTOCOL_SOCKET_REQUEST*)malloc(sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2);
    if (NULL==req) {
        LOG_E("分配日志发包空间失败");
        return;
    }

    req->head.start_flag = PROTOCOL_TCP_STARTFLAG_REQ;
    req->head.cmd = PROTOCOL_TCPCMD_SENDLOG;
    *(unsigned short*)req->head.lenght = sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2;
    LOG_I("包长度 %d\n", *(unsigned short*)req->head.lenght);
    *(unsigned short*)req->pkg_num = _transInfo.pkg_num;
    *(unsigned short*)req->pkg_order = order;

    // 填充内容
    _file->read((char*)req->data, pkg_size);
#if 0
    for (int i=0;i<pkg_size;i++) {
        printf("%02x ", *((char*)req->data+i));
    }
#endif
    // 加校验
    p_ch = (char*)(req+1);
    p_ch += pkg_size;
    *(unsigned short*)p_ch = crc16_xmodem((unsigned char*)req, sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size);

    // 修改传输信息
    _transInfo.pkg_order = order;
    // 发包
    LOG_I("发一包包，%d", order);
    _socket->write((const char*)req, sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2);

#if 0
    //确认是否是最后一包，最后一包，需要回收资源，切换到空闲
    if (order==(_transInfo.pkg_num-1))
    {
        // 最后一包
        LOG_I("最后一包，没有包了");
        resetSendFile();
        _mode = TCPSERVER_IDEL;
    }
#endif
    free(req);
    emit signalTcpReadProgress(100*order/(_transInfo.pkg_num));
}

int Tcp_Server::recvAck(const PROTOCOL_SOCKET_ACK* ack)
{
    unsigned short len = sizeof(PROTOCOL_SOCKET_ACK);
    unsigned short order;
    // 校验是ack
    if (PROTOCOL_TCP_PKGACK_ISHEAD!=protocolSocket_isPkgAck(ack))
    {
        // 不是ack，丢弃
        LOG_E("校验头失败，这一包ack无效，丢弃\n");
        return ACK_INVALIDE;
    }
    // crc校验
    if (CRC16_CHECK_FAILED==crc16_check((unsigned char*)ack, len-2,
                                        *(unsigned short*)((char*)ack+len-2)))
    {
        LOG_E("crc校验失败，这一包ack无效，丢弃\n");
        return ACK_INVALIDE;
    }

    // 判断命令一致
    if (ack->head.cmd!=_transInfo.cmd)
    {
        LOG_E("命令不一致，中断该指令\n");
        return ACK_INVALIDE;
    }
    // 获取序号,请求的序号
    order = *(unsigned short*)ack->pkg_order;
    // 返回序号
    return order;
}

// 处理首包，有可能是日志上传指令
void Tcp_Server::firstPkg(const PROTOCOL_SOCKET_REQUEST* pkg)
{
    const PROTOCOL_SOCKET_REQUEST* req = pkg;
    const PROTOCOL_SOCKET_REQUEST_APPUP* req_appup = (const PROTOCOL_SOCKET_REQUEST_APPUP*)pkg;
    const PROTOCOL_SOCKET_REQUEST_IMGDN* req_imgdn = (const PROTOCOL_SOCKET_REQUEST_IMGDN*)pkg;

    unsigned short pkg_num = *(unsigned short*)req->pkg_num;

    // 修改传输信息
    _transInfo.cmd = req->head.cmd;
    _transInfo.pkg_order = 0;
    _transInfo.pkg_num = *((unsigned short*)(req->pkg_num));

    // 切换工作模式
    switch (req->head.cmd)
    {
    case PROTOCOL_TCPCMD_APPUPDATE:
        // 判断设备类型是否正确，不正确返回一个错误ack，直接返回，保持空闲状态
        if (req_appup->dev_type!=YT328_READER)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_APPTYPE);
            return ;
        }

        // 判断版本号检查
        // 后面的小，返回 >0
        LOG_I("下发版本 %s\n", req_appup->soft_version);
        if (strncmp(APP_VERSION, (const char*)(req_appup->soft_version), 7)>=0)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_APPVER);
            return ;
        }

        // 修改总包数
        _transInfo.pkg_num = *((unsigned short*)(req_appup->pkg_num));
        _mode = TCPSERVER_UPAPP;
        break;
    case PROTOCOL_TCPCMD_GETLOG:
        // 日志上传，切换模式
        _mode = TCPSERVER_GETLOG;
        // 先压缩一个日志包
        if (0==is_file_exist(TMP_LOG_ZIP))
            file_remove(TMP_LOG_ZIP);
        system("zip " PROJECT_DIR_TMP"/log_package.zip " PROJECT_DIR_LOG";sync");
        // 先给一个ack
        sendAck(PROTOCOL_SOCKET_ACKCODE_OK_CONNECT);
        _socket->flush();
        usleep(400000);
        // 解析日志上传命令，并发出首包
        sendFirstLogPkg();
        return;
        break;
    case PROTOCOL_TCPCMD_FACEFEAT:
    {
        if (g_BaseInfo.deviceStatusBeat&DEVICESTATUS_MASK_BEAT)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            return ;
        }
        _mode = TCPSERVER_FEATDN;
        break;
    }
    case PROTOCOL_TCPCMD_FACEIMGS:
    {
        if (g_BaseInfo.deviceStatusBeat&DEVICESTATUS_MASK_BEAT)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            return ;
        }
        _mode = TCPSERVER_IMGSDN;
        break;
    }
    case PROTOCOL_TCPCMD_FACEIMG:
    {
        if (g_BaseInfo.deviceStatusBeat&DEVICESTATUS_MASK_BEAT)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            return ;
        }
        _transInfo.pkg_num = *((unsigned short*)(req_imgdn->pkg_num));
        _mode = TCPSERVER_IMGDN;
        break;
    }
    case PROTOCOL_TCPCMD_DELFACE:
    {
        if (g_BaseInfo.deviceStatusBeat&DEVICESTATUS_MASK_BEAT)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            return ;
        }
        emit signalTcpReadOver(PROTOCOL_TCPCMD_DELFACE);
        _mode = TCPSERVER_FACEDEL;
        // 调用接口处理删除人脸
        if (faceDetect_offline::facedetect_offline_delsingle((const char*)req_imgdn->accnum, (const char*)req_imgdn->cardno)<0)
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            LOG_I("删除人脸失败，切换到空闲\n");
        }
        else
        {
            sendAck(PROTOCOL_SOCKET_ACKCODE_OK_OVER);
            LOG_I("删除人脸成功，切换到空闲\n");
        }
        emit signalWorkDone(PROTOCOL_TCPCMD_DELFACE);
        _mode = TCPSERVER_IDEL;
        return ;
        break;
    }
    default:
        // 不合法的cmd，报错退出
        return;
        break;
    }

    LOG_I("传输信息，总包数 %d\n", _transInfo.pkg_num);

    // 处理首包数据
    storeRequestData(req);
    // 发送ack
    sendAck(PROTOCOL_SOCKET_ACKCODE_OK_NEXT);
    emit signalTcpReadStart(req->head.cmd);
    // 如果只有1包数据，切换到空闲
    if (1==pkg_num)
    {
        LOG_I("只有一包数据，切换到空闲\n");
        _mode = TCPSERVER_IDEL;
        // 处理文件，升级或其他
        if (0==storeFileSuccess(req))
            emit signalTcpReadOver(req->head.cmd);
    }
}

void Tcp_Server::sendFirstLogPkg()
{
    unsigned short num_short = 0;
    unsigned int file_size = 284740;
    unsigned short pkg_size = 0;
    char* p_ch = NULL;

    _file = new QFile(TMP_LOG_PACKAGE_UPLOAD);
    if (!_file->exists())
    {
        LOG_E("日志文件打开失败，首包log发送失败\n");
        return;
    }

    _file->open(QIODevice::ReadOnly);
    // 统计文件大小，计算分包个数
    file_size = _file->size();
    LOG_I("日志文件大小 %d\n", file_size);

    num_short = file_size/DATA_SIZE;
    LOG_I("第一阶段计算包数 %d\n", num_short);
    if (file_size%DATA_SIZE)
    {
        num_short++;
    }
    LOG_I("第二阶段计算包数 %d\n", num_short);

    _transInfo.pkg_num = num_short;
    // 修改传输信息
    _transInfo.cmd = PROTOCOL_TCPCMD_SENDLOG;
    _transInfo.pkg_order = 0;
    LOG_I("传输信息，总包数 %d\n", _transInfo.pkg_num);

    if (1==_transInfo.pkg_num)
    {
        // 如果只有一包，分配文件大小
        pkg_size = file_size;
    }
    else
    {
        // 首包是整包
        pkg_size = DATA_SIZE;
    }

    // 分配空间
    PROTOCOL_SOCKET_REQUEST *req = (PROTOCOL_SOCKET_REQUEST*)malloc(sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2);
    if (NULL==req)
    {
        LOG_E("分配日志发包空间失败");
        return;
    }

    req->head.start_flag = PROTOCOL_TCP_STARTFLAG_REQ;
    req->head.cmd = PROTOCOL_TCPCMD_SENDLOG;
    *(unsigned short*)req->head.lenght = sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2;
    LOG_I("包长度 %d\n", *(unsigned short*)req->head.lenght);
    *(unsigned short*)req->pkg_num = _transInfo.pkg_num;
    *(unsigned short*)req->pkg_order = 0;

    // 填充内容
    _file->read((char*)req->data, pkg_size);

#if 0
    for (int i=0;i<pkg_size;i++)
    {
        printf("%02x ", *((char*)req->data+i));
    }
#endif

    // 加校验
    p_ch = (char*)(req+1);
    p_ch += pkg_size;
    *(unsigned short*)p_ch = crc16_xmodem((unsigned char*)req, sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size);
    // 发包
    _socket->write((const char*)req, sizeof(PROTOCOL_SOCKET_REQUEST)+pkg_size+2);
    LOG_I("发包结束");
    free(req);
    //
    emit signalTcpReadStart(PROTOCOL_TCPCMD_SENDLOG);
}

void Tcp_Server::storeRequestData(const PROTOCOL_SOCKET_REQUEST* req)
{
    // app升级协议有些不同
    PROTOCOL_SOCKET_REQUEST_APPUP* req_appup = (PROTOCOL_SOCKET_REQUEST_APPUP*)req;
    PROTOCOL_SOCKET_REQUEST_IMGDN* req_imgdn = (PROTOCOL_SOCKET_REQUEST_IMGDN*)req;
    LOG_D("处理一帧数据，序号 %d\n", *(unsigned short*)req->pkg_order);
    // 数据长度
    unsigned short len = *(unsigned short*)(req->head.lenght);
    //
    switch (req->head.cmd)
    {
    case PROTOCOL_TCPCMD_APPUPDATE:
        // 写入app更新文件
        file_append(TMP_UPDATE_PACKAGE_DOWNLOAD, (const char*)req_appup->data, len-26);
        //file_append(TMP_UPDATE_PACKAGE_DOWNLOAD, "123", 3);
        break;
    case PROTOCOL_TCPCMD_GETLOG:
        break;
    case PROTOCOL_TCPCMD_FACEFEAT:
        // 写入特征值文件
        file_append(PROJECT_DIR_TMP"/face_feat_package.tar.gz", (const char*)req->data, len-25);
        break;
    case PROTOCOL_TCPCMD_FACEIMGS:
        // 写入人脸图片压缩文件
        file_append(TMP_FACEIMG_PACKAGE_DOWNLOAD, (const char*)req->data, len-25);
        break;
    case PROTOCOL_TCPCMD_FACEIMG:
        file_append(TMP_IMGFACE, (const char*)req_imgdn->data, len-61);
        break;
    case PROTOCOL_TCPCMD_DELFACE:
        break;
    default:
        break;
    }
}

int Tcp_Server::storeFileSuccess(const PROTOCOL_SOCKET_REQUEST *req)
{
    const PROTOCOL_SOCKET_REQUEST_APPUP* req_appup = (const PROTOCOL_SOCKET_REQUEST_APPUP*)req;
    switch (req->head.cmd)
    {
    case PROTOCOL_TCPCMD_APPUPDATE:
        // 校验文件
        if (CRC16_CHECK_FAILED==crc16_fileCheck(PROJECT_DIR_TMP"/update_app_package.tar.gz", *((const unsigned short*)(req_appup->check))))
        {
            LOG_E("校验app更新包失败，中断升级\n");
            emit signalCrcCheckFailed();
            if (0==is_file_exist(TMP_UPDATE_PACKAGE_DOWNLOAD))
                file_remove(TMP_UPDATE_PACKAGE_DOWNLOAD);
            return -1;
        }
        system("tar xf " PROJECT_DIR_TMP"/update_app_package.tar.gz -C /data;sync");
        // 更新完删除文件
        if (0==is_file_exist(TMP_UPDATE_PACKAGE_DOWNLOAD))
            file_remove(TMP_UPDATE_PACKAGE_DOWNLOAD);
        break;
    case PROTOCOL_TCPCMD_GETLOG:
        break;
    case PROTOCOL_TCPCMD_FACEFEAT:
        _mode = TCPSERVER_THREAD_FEAT;
        this->start();
        break;
    case PROTOCOL_TCPCMD_FACEIMGS:
        // 校验文件
        if (CRC16_CHECK_FAILED==crc16_fileCheck(PROJECT_DIR_TMP"/face_img_package.tar.gz", *(unsigned short*)req->check))
        {
            LOG_E("校验人脸图片压缩包失败，中断加入人脸\n");
            // 发送错误信号
            emit signalCrcCheckFailed();
            if (0==is_file_exist(TMP_FACEIMG_PACKAGE_DOWNLOAD))
                file_remove(TMP_FACEIMG_PACKAGE_DOWNLOAD);
            return -1;
        }
        // 解压图片压缩包
        system("tar xf " PROJECT_DIR_TMP"/face_img_package.tar.gz -C " PROJECT_DIR_TMP);
        // 更新完删除压缩包
        if (0==is_file_exist(TMP_FACEIMG_PACKAGE_DOWNLOAD))
            file_remove(TMP_FACEIMG_PACKAGE_DOWNLOAD);
        // 开线程，转特征码
        _mode = TCPSERVER_THREAD_FEATIMGS;
        this->start();
        break;
    case PROTOCOL_TCPCMD_FACEIMG:
        // 校验文件
        // 开线程，转码
        _mode = TCPSERVER_THREAD_FEATIMG;
        this->start();
        // 转码
        break;
    default:
        break;
    }

    return 0;
}

// 清理缓存
void Tcp_Server::resetReadBuffer()
{
    if (0!=_bufferOffset)
    {
        LOG_I("复位缓存\n");
        // 使用了分配缓存，清理
        free(_readBuffer);
        _readBuffer = 0;
        _bufferLeft = 0;
        _bufferOffset = 0;
        _isPacket = false;
    }
}

// 清理文件
void Tcp_Server::resetSendFile()
{
    if (NULL!=_file)
    {
        _file->close();
        delete _file;
        _file = NULL;
    }
}

void Tcp_Server::run()
{
    PROTOCOL_SOCKET_REQUEST_IMGDN* req_imgdn = (PROTOCOL_SOCKET_REQUEST_IMGDN*)_readBuffer;
    switch (_mode)
    {
    case TCPSERVER_THREAD_FEATIMGS:
        faceDetect_offline::facedetect_offline_add();
        emit signalWorkDone(PROTOCOL_TCPCMD_FACEIMGS);
        _mode = TCPSERVER_IDEL;
        break;
    case TCPSERVER_THREAD_FEATIMG:
#if 1
        faceDetect_offline::facedetect_offline_addsingle((const char*)req_imgdn->accnum,
                                                         (const char*)req_imgdn->cardno,
                                                         (const char*)req_imgdn->name);
#endif
        emit signalWorkDone(PROTOCOL_TCPCMD_FACEIMG);
        _mode = TCPSERVER_IDEL;
        resetReadBuffer();
#if 1
        if (0==is_file_exist(TMP_IMGFACE))
            file_remove(TMP_IMGFACE);
#endif
        break;
    case TCPSERVER_THREAD_FEAT:
        emit signalWorkDone(PROTOCOL_TCPCMD_FACEFEAT);
        break;
    default:
        break;
    }
}

void Tcp_Server::slotNewConnection()
{
    _pkg_crc16 = 0;
    QTcpSocket* socket = _tcpServer.nextPendingConnection();
    _socket = socket;
    connect(socket, SIGNAL(disconnected()), this, SLOT(slotSocketDisconnect()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(slotReadyRead()));
    LOG_I("tcp服务连接\n");
    emit signalTcpConnected(true);
}

void Tcp_Server::slotSocketDisconnect()
{
    _pkg_crc16 = 0;
    LOG_I("tcp服务断开");
    ((QTcpSocket*)sender())->deleteLater();
    // 清理传输信息
    _mode = TCPSERVER_IDEL;
    memset(&_transInfo, 0, sizeof(_transInfo));
    _socket = NULL;
    resetReadBuffer();
    resetSendFile();
    emit signalTcpConnected(false);
}

void Tcp_Server::slotReadyRead()
{
    QByteArray array = ((QTcpSocket*)sender())->readAll();
    int ret = 0;
    // 获取数据首地址（有可能是req或者ack）
    const PROTOCOL_SOCKET_REQUEST* data = (const PROTOCOL_SOCKET_REQUEST*)(array.constData());
    const PROTOCOL_SOCKET_ACK* ack = (const PROTOCOL_SOCKET_ACK*)data;
    const PROTOCOL_SOCKET_REQUEST_APPUP* req_appup = NULL;
    const PROTOCOL_SOCKET_REQUEST_IMGDN* req_imgdn = NULL;

    // 解析头，获取数据长度
    int len = *(unsigned short*)data->head.lenght;
    // 获取包序号
    unsigned short order = *(unsigned short*)data->pkg_order;

    LOG_I("收到一包数据，长度 %d", len);
    // 如果是在跑线程，不响应tcp包
    switch (_mode)
    {
    case TCPSERVER_THREAD_FEATIMGS:
    case TCPSERVER_THREAD_FEATIMG:
    case TCPSERVER_THREAD_FEAT:
    case TCPSERVER_THREAD_FILEUP:
        return;
        break;
    case TCPSERVER_GETLOG:
        // 上传日志，校验为ack，这里比较短，能收到整包，不用考虑拼包
        // 校验ack，并确认是否发下一包
        ret = recvAck(ack);
        if (ACK_INVALIDE==ret)
        {
            // 无效ack，中断日志发送，进入空闲
            LOG_I("收到无效ack，中断日志发送，进入空闲\n");
            resetSendFile();
            _mode = TCPSERVER_IDEL;
            return ;
        }
        LOG_I("收到有效ack，请求序号 %d\n", ret);
        // 继续发包，从传输信息获取之前发包信息，指定发包序号
        sendReq((unsigned short)ret);
        return;
        break;
    case TCPSERVER_FACEDEL:
        // 删除人脸模式下，不响应任何请求
        return ;
        break;
    case TCPSERVER_IDEL:
    case TCPSERVER_UPAPP:
    case TCPSERVER_FEATDN:
    case TCPSERVER_IMGSDN:
    case TCPSERVER_IMGDN:
        break;
    case TCPSERVER_BUSY:
        // 繁忙状态，不响应
    default:
        return;
        break;
    }

#if 0
    for (int i=0;i<array.length();i++) {
        printf("%02x ", *((char*)data+i));
    }
    printf("\n");
#endif

#if 1
    // 验证包含包头
    if (PROTOCOL_TCP_PKGREQ_ISHEAD==protocolSocket_isPkgReq(data) && !_isPacket)
    {
        // 判断这次收到数据是否等于包长
        if (len==array.length())
        {
            //
            LOG_I("完整包，直接处理\n");
            _readBuffer = (PROTOCOL_SOCKET_REQUEST*)data;
            goto pkg_optStatrt;
        }
        LOG_I("包长%d，数据长度%d，包含头的不完整包，分配缓存\n", len, array.length());
        // 分配缓存
        if (0!=_readBuffer)
        {
            LOG_I("缓存未清理\n");
            resetReadBuffer();
        }
        _readBuffer = (PROTOCOL_SOCKET_REQUEST*)calloc(len, 1);
        memset(_readBuffer, 0 , len);
        // 填充
        memcpy(_readBuffer, data, array.length());
        _bufferLeft = len-array.length();
        _bufferOffset = array.length();
        // 返回等待下一帧，进入拼包流程
        _isPacket = true;
        return;
    }
    else
    {
        // 不包含包头，需要不是空闲才处理
        if (array.length()<_bufferLeft)
        {
            //
            LOG_I("数据长度%d，剩余空间%d，剩余控件充足，拼包\n", array.length(), _bufferLeft);
            memcpy((char*)_readBuffer+_bufferOffset, data, array.length());
            _bufferLeft -= array.length();
            _bufferOffset += array.length();
            return;
        }
        else if (array.length()==_bufferLeft)
        {
            // 拼包结束
            LOG_I("数据长度%d，剩余空间%d，拼包结束，处理数据\n", array.length(), _bufferLeft);
            memcpy((char*)_readBuffer+_bufferOffset, data, array.length());
            _bufferLeft -= array.length();
            _bufferOffset += array.length();
            // 结束拼包
            _isPacket = false;
            // 处理数据包
            goto pkg_optStatrt;
        }
        else
        {
            LOG_I("空间不充足，跨包了，不处理\n");
            resetReadBuffer();
            emit signalTransFailed();
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            return;
        }
    }
#endif


    // 开始处理完整包数据，收到的包有可能是不同的类型
pkg_optStatrt:
    // 获取包长度
    len = *(unsigned short*)(_readBuffer->head.lenght);
    // 获取包序号
    order = *(unsigned short*)(_readBuffer->pkg_order);

#if 0
    for (int i=0;i<len;i++) {
        printf("%02x ", *((char*)_readBuffer+i));
    }
#endif

    LOG_I("命令 %02x， 包总数 %d， 当前序号 %d，长度 %d,%d\n",
          _readBuffer->head.cmd, *(unsigned short*)_readBuffer->pkg_num,
          *(unsigned short*)_readBuffer->pkg_order, len, array.length());

    // crc校验，校验失败，返回
    if (CRC16_CHECK_FAILED==crc16_check((unsigned char*)_readBuffer, len-2,
                                        *(unsigned short*)((char*)_readBuffer+len-2)))
    {
        LOG_E("crc校验失败，返回，丢弃这一包数据， 请求包\n");
        sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_AGAIN);
        // 清理缓存，返回
        resetReadBuffer();
        return;
    }

    // 解析数据包，,处理请求包
    switch (_mode)
    {
    case TCPSERVER_IDEL:
    {
        // 只有是空闲的时候收到首包才正确
        if (PROTOCOL_TCP_PKGREQ_FIRST==protocolSocket_isFirstReq(_readBuffer))
        {
            // 处理首包
            LOG_I("发现首包，处理首包\n");
            firstPkg(_readBuffer);
            resetReadBuffer();
            return;
        }
        else
        {
            // 不是首包，不合法
            LOG_I("空闲，收到非首包，返回，丢弃这一包\n");
            sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INVALIDE);
            resetReadBuffer();
            return ;
        }
        break;
    }
    case TCPSERVER_GETLOG:
        // 获取日志模式，处理ack，处理结束返回
        // 处理ack在函数开头
        return;
        break;
    case TCPSERVER_UPAPP:
    {
        // 升级包，需要转协议
        req_appup = (const PROTOCOL_SOCKET_REQUEST_APPUP*)_readBuffer;
        order = *(unsigned short*)(req_appup->pkg_order);
        break;
    }
    case TCPSERVER_IMGDN:
    {
        // 单张图片包，需要转协议
        req_imgdn = (const PROTOCOL_SOCKET_REQUEST_IMGDN*)_readBuffer;
        order = *(unsigned short*)(req_imgdn->pkg_order);
        break;
    }
    case TCPSERVER_FEATDN:
    case TCPSERVER_IMGSDN:
        break;
    default:
        break;
    }

    if (_readBuffer->head.cmd!=_transInfo.cmd)
    {
        // 命令码不一致，传输中断，切换空闲，返回
        LOG_I("命令码不一致，传输中断，丢弃这一包，返回\n");
        _mode = TCPSERVER_IDEL;
        sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_INTERUPT);
        resetReadBuffer();
        return;
    }

    // 判断序号，是否自增序号
    if (order!=(_transInfo.pkg_order+1))
    {
        // 不是自增，ack重新发包
        LOG_I("当前序号%d，接受包序号%d，收到不是下一包，丢弃这一包，请求重发，返回\n",
              _transInfo.pkg_order, order);
        sendAck(PROTOCOL_SOCKET_ACKCODE_FAILE_AGAIN);
        resetReadBuffer();
        return ;
    }

    // 判断是否是最后一包
    if (order==(_transInfo.pkg_num-1))
    {
        // 最后一包
        LOG_I("收到最后一包，处理最后一包\n");
        _mode = TCPSERVER_IDEL;
        // 修改序号，处理数据
        _transInfo.pkg_order = order;
        storeRequestData(_readBuffer);
        sendAck(PROTOCOL_SOCKET_ACKCODE_OK_OVER);
        // 处理文件，升级或其他，出错
        if (0==storeFileSuccess(_readBuffer))
        {
            LOG_I("发出结束信号\n");
            emit signalTcpReadOver(_readBuffer->head.cmd);
        }
        // 复位buffer
        // 不是单张图片线程，复位缓存，单张图片，复位延后
        if (TCPSERVER_THREAD_FEATIMG!=_mode)
            resetReadBuffer();
        return;
    }

    // 不是最后一包
    LOG_I("当前序号%d，接受包序号%d，成功收到一包，请求下一包\n",
          _transInfo.pkg_order, order);
    // 修改序号，处理数据
    _transInfo.pkg_order = order;
    storeRequestData(_readBuffer);
    sendAck(PROTOCOL_SOCKET_ACKCODE_OK_NEXT);
    emit signalTcpReadProgress(100*order/(_transInfo.pkg_num));
    resetReadBuffer();
    return;
}

