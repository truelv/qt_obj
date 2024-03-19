#include "rtcmanager.h"
#include <iostream>
#include <memory>
#include <vector>
//
#include "api/jsep.h"
#include "rtc_base/ssl_adapter.h"
#include "rtc_base/thread.h"

RTCManager::RTCManager()
{
    // 初始化SSL（必要步骤）
    rtc::InitializeSSL();
}

RTCManager::~RTCManager()
{
    rtc::CleanupSSL();
}

void RTCManager::CreatePeerConnection()
{
    // 创建PeerConnection的配置
    webrtc::PeerConnectionInterface::RTCConfiguration config;
    // ...配置STUN/TURN服务器等

    // 创建PeerConnection
    _peer_connection = _peer_connection_factory->CreatePeerConnection(
                config, NULL, NULL, this);
    if (!_peer_connection) {
        Error("创建PeerConnection失败");
        return;
    }

    // 添加媒体流等逻辑处理
    // ...
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
#endif

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

void RTCManager::Log(const std::string &message)
{
    cout << message;
}

void RTCManager::Error(const std::string &message)
{
    cerr << message;
}
