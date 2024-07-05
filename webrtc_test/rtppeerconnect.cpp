#include "rtppeerconnect.h"

#include <QImage>
#include <QDebug>

#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/video_codecs/builtin_video_encoder_factory.h"
#include "api/video_codecs/builtin_video_decoder_factory.h"
#include "pc/video_track_source.h"
#include "test/vcm_capturer.h"

#include "serverconnectbase.h"

 class CapturerTrackSource : public webrtc::VideoTrackSource {
  public:
   static rtc::scoped_refptr<CapturerTrackSource> Create() {
     const size_t kWidth = 640;
     const size_t kHeight = 480;
     const size_t kFps = 30;
     const size_t kDeviceIndex = 0;
     std::unique_ptr<webrtc::test::VcmCapturer> capturer = absl::WrapUnique(
         webrtc::test::VcmCapturer::Create(kWidth, kHeight, kFps, kDeviceIndex));
     if (!capturer) {
       return nullptr;
     }
     return new rtc::RefCountedObject<CapturerTrackSource>(std::move(capturer));
   }

  protected:
   explicit CapturerTrackSource(
       std::unique_ptr<webrtc::test::VcmCapturer> capturer)
       : VideoTrackSource(/*remote=*/false), capturer_(std::move(capturer)) {}

  private:
   rtc::VideoSourceInterface<webrtc::VideoFrame>* source() override {
     return capturer_.get();
   }
   std::unique_ptr<webrtc::test::VcmCapturer> capturer_;
 };


RtpPeerConnect::RtpPeerConnect()
{

}

RtpPeerConnect::~RtpPeerConnect()
{

}
#include "rtc_base/ssl_adapter.h"
#include "api/create_peerconnection_factory.h"
void RtpPeerConnect::connectPeer()
{
    rtc::InitializeSSL();
    std::unique_ptr<rtc::Thread> signalingThread = rtc::Thread::Create();
    signalingThread->Start();
    _peer_connection_factory = webrtc::CreatePeerConnectionFactory(
                nullptr,
                nullptr,
                signalingThread.get(),
                nullptr,
                webrtc::CreateBuiltinAudioEncoderFactory(),
                webrtc::CreateBuiltinAudioDecoderFactory(),
                webrtc::CreateBuiltinVideoEncoderFactory(),
                webrtc::CreateBuiltinVideoDecoderFactory(),
                nullptr,
                nullptr);
    if (NULL==_peer_connection_factory.get()) {
        qDebug() << "create peer connect factory error";
        return ;
    }

    // 创建PeerConnection的配置
    webrtc::PeerConnectionInterface::RTCConfiguration config;
    config.sdp_semantics = webrtc::SdpSemantics::kUnifiedPlan;
    config.enable_dtls_srtp = true;
    // ...配置STUN/TURN服务器等
    webrtc::PeerConnectionInterface::IceServer server;
    server.uri = "stun:stun.l.google.com:19302";
    config.servers.push_back(server);
    // 创建PeerConnection
    _peer_connection = _peer_connection_factory->CreatePeerConnection(
                config, nullptr, nullptr, this);
    if (NULL==_peer_connection.get()) {
        qDebug() << "create peer connect error";
        return ;
    }

    // 音频轨道
    rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track(
                _peer_connection_factory->CreateAudioTrack(
                    "audio_label", _peer_connection_factory->CreateAudioSource(
                        cricket::AudioOptions())));
    if (NULL==audio_track.get()) {
        qDebug() << "create audio track error";
        return ;
    }
    auto result_or_error = _peer_connection->AddTrack(audio_track, {"stream_id"});
    if (!result_or_error.ok()) {
        qDebug() << "add audio track error";
        return ;
    }

    // 视频轨道
    // 源
    rtc::scoped_refptr<CapturerTrackSource> vsource = CapturerTrackSource::Create();
    if (NULL==vsource.get()) {
        qDebug() << "create video source error";
        return ;
    }
    // 视频轨
    rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(
             _peer_connection_factory->CreateVideoTrack("video_label", vsource));;
    if (NULL==video_track_.get()) {
        qDebug() << "create video track error";
        return ;
    }
    // 初始化本地采集器
    _local_renderer.reset(new VideoRenderer(video_track_));
    result_or_error = _peer_connection->AddTrack(video_track_, {"stream_id"});
    if (!result_or_error.ok()) {
        qDebug() << "add audio track error";
        return ;
    }

    qDebug() << "page 3";

    //
    _peer_connection->CreateOffer(this, webrtc::PeerConnectionInterface::RTCOfferAnswerOptions());
}

void RtpPeerConnect::OnAddTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver, const std::vector<rtc::scoped_refptr<webrtc::MediaStreamInterface> > &streams)
{
    qDebug() << "new track add";
}

void RtpPeerConnect::OnRemoveTrack(rtc::scoped_refptr<webrtc::RtpReceiverInterface> receiver)
{
    qDebug() << "track remove";
}

void RtpPeerConnect::OnIceCandidate(const webrtc::IceCandidateInterface *candidate)
{
    qDebug() << "OnIceCandidate";
}

class DummySetSessionDescriptionObserver
        : public webrtc::SetSessionDescriptionObserver {
public:
    static DummySetSessionDescriptionObserver* Create() {
        return new rtc::RefCountedObject<DummySetSessionDescriptionObserver>();
    }
    virtual void OnSuccess() { RTC_LOG(INFO) << __FUNCTION__; }
    virtual void OnFailure(webrtc::RTCError error) {
        RTC_LOG(INFO) << __FUNCTION__ << " " << ToString(error.type()) << ": "
                      << error.message();
    }
};

#if 1
#include "rtc_base/strings/json.h"
void RtpPeerConnect::OnSuccess(webrtc::SessionDescriptionInterface *desc)
{
    qDebug() << "ask OK";
    DummySetSessionDescriptionObserver* sess = DummySetSessionDescriptionObserver::Create();
    if (NULL==sess) {
        qDebug() << "SessionDescription create error";
        return ;
    }
    _peer_connection->SetLocalDescription(sess, desc);
#if 1
    std::string sdp;
    desc->ToString(&sdp);
#endif

#if 0
    // For loopback test. To save some connecting delay.
    if (false) {
      // Replace message type from "offer" to "answer"
      std::unique_ptr<webrtc::SessionDescriptionInterface> session_description =
          webrtc::CreateSessionDescription(webrtc::SdpType::kAnswer, sdp);
      _peer_connection->SetRemoteDescription(
          DummySetSessionDescriptionObserver::Create(),
          session_description.release());
      return;
    }
#endif

#if 0
    ServerConnectBase* sc = ServerConnectBase::getIntent();
    char* sendbuf = (char*)calloc(1,2048);

    char* sdpstr = "{"
                "\"sdp\" : \"v=0\r\no=- 3709718496152863382 2 IN IP4 127.0.0.1\r\ns=-\r\nt=0 0\r\na=group:BUNDLE 0\r\na=msid-semantic: WMS stream_id\r\nm=audio 9 UDP/TLS/RTP/SAVPF 111 103 104 9 102 0 8 106 105 13 110 112 113 126\r\nc=IN IP4 0.0.0.0\r\na=rtcp:9 IN IP4 0.0.0.0\r\na=ice-ufrag:KaJB\r\na=ice-pwd:lq9On5ksSCJlnLN31dDi0IuK\r\na=ice-options:trickle\r\na=fingerprint:sha-256 73:95:B5:78:F3:C2:CB:95:9D:40:EC:BB:25:2C:21:C7:E8:74:52:9E:E8:B8:C7:C9:0E:80:6E:1B:1B:95:CA:87\r\na=setup:actpass\r\na=mid:0\r\na=extmap:1 urn:ietf:params:rtp-hdrext:ssrc-audio-level\r\na=extmap:2 http://www.webrtc.org/experiments/rtp-hdrext/abs-send-time\r\na=extmap:3 http://www.ietf.org/id/draft-holmer-rmcat-transport-wide-cc-extensions-01\r\na=extmap:4 urn:ietf:params:rtp-hdrext:sdes:mid\r\na=extmap:5 urn:ietf:params:rtp-hdrext:sdes:rtp-stream-id\r\na=extmap:6 urn:ietf:params:rtp-hdrext:sdes:repaired-rtp-stream-id\r\na=sendrecv\r\na=msid:stream_id audio_label\r\na=rtcp-mux\r\na=rtpmap:111 opus/48000/2\r\na=rtcp-fb:111 transport-cc\r\na=fmtp:111 minptime=10;useinbandfec=1\r\na=rtpmap:103 ISAC/16000\r\na=rtpmap:104 ISAC/32000\r\na=rtpmap:9 G722/8000\r\na=rtpmap:102 ILBC/8000\r\na=rtpmap:0 PCMU/8000\r\na=rtpmap:8 PCMA/8000\r\na=rtpmap:106 CN/32000\r\na=rtpmap:105 CN/16000\r\na=rtpmap:13 CN/8000\r\na=rtpmap:110 telephone-event/48000\r\na=rtpmap:112 telephone-event/32000\r\na=rtpmap:113 telephone-event/16000\r\na=rtpmap:126 telephone-event/8000\r\na=ssrc:3235820052 cname:svy7AaG4eaWSw3Z9\r\na=ssrc:3235820052 msid:stream_id audio_label\r\na=ssrc:3235820052 mslabel:stream_id\r\na=ssrc:3235820052 label:audio_label\r\n\","
                "\"type\" : \"offer\""
                "}";

    snprintf(sendbuf, 2048,
             "POST /message?peer_id=%i&to=42 HTTP/1.0\r\n"
             "Content-Length: %zu\r\n"
             "Content-Type: text/plain\r\n"
             "\r\n", sc->id(), strlen(sdpstr));
    unsigned int llen = strlen(sendbuf);
#if 1
    snprintf(sendbuf+llen, 2048-llen, "%s", sdpstr);
#endif
    qDebug() << sendbuf;
    sc->sendSignalSendsocket(sendbuf, strlen(sendbuf));
#endif
}

void RtpPeerConnect::OnFailure(webrtc::RTCError error)
{
    qDebug() << "ask err "<< error.message();
}
#endif

RtpPeerConnect::VideoRenderer::VideoRenderer(webrtc::VideoTrackInterface *track_to_render):
    _rendered_track(track_to_render)
{
    _rendered_track->AddOrUpdateSink(this, rtc::VideoSinkWants());
}

void RtpPeerConnect::VideoRenderer::OnFrame(const webrtc::VideoFrame &frame)
{

}
