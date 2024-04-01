#ifndef RTPPEERCONNECT_H
#define RTPPEERCONNECT_H

#include "api/create_peerconnection_factory.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "rtc_base/ssl_adapter.h"

class RtpPeerConnect
{
public:
    RtpPeerConnect();
    ~RtpPeerConnect();

    void connectPeer();

private:
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer_connection;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer_connection_factory;
};

#endif // RTPPEERCONNECT_H
