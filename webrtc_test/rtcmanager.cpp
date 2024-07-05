#include "rtcmanager.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
//
#include "rtc_base/ssl_adapter.h"
#include "rtc_base/thread.h"
#include "rtc_base/signal_thread.h"
#include "rtc_base/third_party/sigslot/sigslot.h"
#include "api/create_peerconnection_factory.h"
#include "api/jsep.h"


RTCManager::RTCManager() :
    _state(NOT_CONNECTED)
{
    // 初始化SSL（必要步骤）
    rtc::InitializeSSL();
}

RTCManager::~RTCManager()
{
    //rtc::Thread::Current()->Clear(this);
    rtc::CleanupSSL();
}

int RTCManager::ConnectServer(const char *addr, unsigned int port, const char* clientName)
{
    if (NULL==addr || NULL==clientName)
        return -1;

    // 检查服务地址的有效性

    if (NOT_CONNECTED!=_state) {
        Error("客户端必须在没有连接的情况下建立连接");
        return -1;
    }

    if (0==port)
        port = 8888;

    Log("连接服务:");
    _server_address.SetIP(addr);
    _server_address.SetPort(port);
    _client_name = clientName;
    // 域名解析？？？
    _state = RESOLVING;

    // 连接服务
    _control_socket.reset(CreateClientSocket(_server_address.ipaddr().family()));
    if (NULL==_control_socket.get()) {
        Error("创建socket失败");
        return -1;
    }

    // 设置回调
    _control_socket->SignalCloseEvent.connect(this, &RTCManager::Control_OnClose);
    _control_socket->SignalConnectEvent.connect(this, &RTCManager::Control_OnConnect);
    _control_socket->SignalReadEvent.connect(this, &RTCManager::Control_OnRead);

    // 请求
    char buffer[64] = {0};
    snprintf(buffer, sizeof(buffer), "GET /sign_in?%s HTTP/1.0\r\n\r\n", _client_name.c_str());
    //Log(buffer);
    int err = _control_socket->Connect(_server_address);
    if (SOCKET_ERROR==err) {
        Error("连接服务失败");
        return -1;
    }
    // 请求的结果将会在回调中处理
    return 0;
}

rtc::AsyncSocket *RTCManager::CreateClientSocket(int family)
{
    rtc::Thread* thread = rtc::Thread::Current();
    if (NULL==thread) {
        Error("获取线程失败");
        return NULL;
    }
    return thread->socketserver()->CreateAsyncSocket(family, SOCK_STREAM);
}

// 创建 Peer Connection
void RTCManager::CreatePeerConnection()
{
    // 创建线程对象，用于处理网络和信令事件
    rtc::Thread networkThread(nullptr);
    rtc::Thread workerThread(nullptr);
    rtc::Thread signalingThread(nullptr);
    networkThread.Start();
    workerThread.Start();
    signalingThread.Start();

    // 创建 PeerConnectionFactory 对象
    _peer_connection_factory = webrtc::CreatePeerConnectionFactory(rtc::Thread::Current(),
                                                                   rtc::Thread::Current(),
                                                                   rtc::Thread::Current(),
                                                                   nullptr,
                                                                   nullptr,
                                                                   nullptr,
                                                                   nullptr,
                                                                   nullptr,
                                                                   nullptr,
                                                                   nullptr);
#if 1
    // 创建PeerConnection的配置
    webrtc::PeerConnectionInterface::RTCConfiguration config;
    // ...配置STUN/TURN服务器等

    // 创建PeerConnection
    _peer_connection = _peer_connection_factory->CreatePeerConnection(
                config, nullptr, nullptr, nullptr);
    if (!_peer_connection) {
        Error("创建PeerConnection失败");
        return;
    }

    // 添加媒体流等逻辑处理
    // ...
#endif
}

#if 0
void RTCManager::CreateSendOffer()
{
    _peer_connection->CreateOffer(
                rtc::scoped_refptr<webrtc::CreateSessionDescriptionObserver>::Create(this),
                webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());
}

void RTCManager::CreateSendAnswer()
{
    _peer_connection->CreateAnswer(
                rtc::scoped_refptr<webrtc::CreateSessionDescriptionObserver>::Create(this),
                webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());
}


void RTCManager::OnIceCandidate(const webrtc::IceCandidateInterface *candidate)
{

}

void RTCManager::OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state)
{
    switch (new_state) {
        case webrtc::PeerConnectionInterface::kIceConnectionConnected:
            Log("ICE连接建立");
            break;
        case webrtc::PeerConnectionInterface::kIceConnectionFailed:
            Error("ICE连接失败");
            break;
        // 其他状态...
    }
}
#endif
void RTCManager::Log(const std::string &message)
{
    std::cout << message << std::endl;
}

void RTCManager::Error(const std::string &message)
{
    std::cerr << message << std::endl;
}

void RTCManager::Control_OnClose(rtc::AsyncSocket *socket, int err)
{
    Log("Control_OnClose");
}

void RTCManager::Control_OnConnect(rtc::AsyncSocket *socket)
{
    Log("Control_OnConnect");
}

void RTCManager::Control_OnRead(rtc::AsyncSocket *socket)
{
    Log("Control_OnRead");
}
