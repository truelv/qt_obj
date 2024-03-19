#ifndef RTCMANAGER_H
#define RTCMANAGER_H

#include "api/scoped_refptr.h"
#include "api/peer_connection_interface.h"

using namespace std;

class RTCManager
{
public:
    RTCManager();
    ~RTCManager();
    //
    void CreatePeerConnection();
    //
#if 0
    void CreateSendOffer();
    void CreateSendAnswer();
#endif
    // 通知其他设备有新的ICE,最佳网络连接路径
    virtual void OnIceCandidate(const webrtc::IceCandidateInterface* candidate);
    // ICE状态变化
    virtual void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state);
    //
    virtual void OnSuccess(webrtc::SessionDescriptionInterface* desc);
    virtual void OnFailure(webrtc::RTCError error);

protected:
    virtual void Log(const std::string& message);
    virtual void Error(const std::string& message);

private:
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer_connection_factory;
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer_connection;
};

#endif // RTCMANAGER_H
