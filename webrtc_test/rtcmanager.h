#ifndef RTCMANAGER_H
#define RTCMANAGER_H
#include <string>
#include "api/peer_connection_interface.h"

// webrtc作为客户端，的连接状态
typedef enum {
    NOT_CONNECTED = 0,
    RESOLVING,
    SIGNING_IN,
    CONNECTED,
    SIGNING_OUT_WAITING,
    SIGNING_OUT,
} RTC_CLIENT_STATE;

class RTCManager :public sigslot::has_slots<>
{
public:
    RTCManager();
    ~RTCManager();

    // 连接服务
    int ConnectServer(const char* addr, unsigned int port, const char *clientName);
    rtc::AsyncSocket* CreateClientSocket(int family);
    //
    void CreatePeerConnection();
    //
#if 0
    void CreateSendOffer();
    void CreateSendAnswer();

    // 通知其他设备有新的ICE,最佳网络连接路径
    virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
    // ICE状态变化
    virtual void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state);
    //
    virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc);
    virtual void OnFailure(webrtc::RTCError error);
#endif
protected:
    virtual void Log(const std::string& message);
    virtual void Error(const std::string& message);

private:
    void Control_OnClose(rtc::AsyncSocket* socket, int err);
    void Control_OnConnect(rtc::AsyncSocket* socket);
    void Control_OnRead(rtc::AsyncSocket* socket);

private:
#if 1
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer_connection_factory;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer_connection;
#endif
    // 客户端状态
    RTC_CLIENT_STATE _state;
    // 服务地址对象，包括地址和端口
    rtc::SocketAddress _server_address;
    // 客户端名称
    std::string _client_name;
    // 连接服务的socket
    std::unique_ptr<rtc::AsyncSocket> _control_socket;
};

#endif // RTCMANAGER_H
