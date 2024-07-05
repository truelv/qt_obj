#ifndef RTPPEERCONNECT_H
#define RTPPEERCONNECT_H

#include <QImage>
#include "api/create_peerconnection_factory.h"
#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "rtc_base/ssl_adapter.h"

class RtpPeerConnect: public webrtc::PeerConnectionObserver,
        public webrtc::CreateSessionDescriptionObserver
{
public:
    RtpPeerConnect();
    ~RtpPeerConnect();
    void connectPeer();

protected:
    // PeerConnectionObserver implementation.
    void OnSignalingChange(webrtc::PeerConnectionInterface::SignalingState new_state) override {}
    void OnAddTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver,
                    const std::vector<rtc::scoped_refptr<webrtc::MediaStreamInterface>>&streams) override;
    void OnRemoveTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver) override;
    void OnDataChannel(rtc::scoped_refptr<webrtc::DataChannelInterface> channel) override {}
    void OnRenegotiationNeeded() override {}
    void OnIceConnectionChange(webrtc::PeerConnectionInterface::IceConnectionState new_state) override {}
    void OnIceGatheringChange(webrtc::PeerConnectionInterface::IceGatheringState new_state) override {}
    void OnIceCandidate(const webrtc::IceCandidateInterface* candidate) override;
    void OnIceConnectionReceivingChange(bool receiving) override {}

#if 1
    // CreateSessionDescriptionObserver implementation.
    void OnSuccess(webrtc::SessionDescriptionInterface* desc) override;
    void OnFailure(webrtc::RTCError error) override;
#endif


private:
    rtc::scoped_refptr<webrtc::PeerConnectionInterface> _peer_connection;
    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> _peer_connection_factory;
    //
    class VideoRenderer : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
    public:
        VideoRenderer(webrtc::VideoTrackInterface* track_to_render);
        void OnFrame(const webrtc::VideoFrame& frame);
        //QImage& _img;
    private:
        unsigned int _incoming_frames;
        rtc::scoped_refptr<webrtc::VideoTrackInterface> _rendered_track;

    };
    std::unique_ptr<VideoRenderer> _local_renderer;
    std::unique_ptr<VideoRenderer> _remote_renderer;
};

#endif // RTPPEERCONNECT_H
