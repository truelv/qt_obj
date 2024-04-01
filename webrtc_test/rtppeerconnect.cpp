#include "rtppeerconnect.h"

#include <QImage>

#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/video_codecs/builtin_video_encoder_factory.h"
#include "api/video_codecs/builtin_video_decoder_factory.h"
#include "pc/video_track_source.h"
#include "test/vcm_capturer.h"


class VideoCallback : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
public:
    VideoCallback(QImage& img);
    void OnFrame(const webrtc::VideoFrame& frame);
    QImage& _img;
private:
    unsigned int _incoming_frames;

};

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
    _peer_connection_factory = webrtc::CreatePeerConnectionFactory(
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                webrtc::CreateBuiltinAudioEncoderFactory(),
                webrtc::CreateBuiltinAudioDecoderFactory(),
                webrtc::CreateBuiltinVideoEncoderFactory(),
                webrtc::CreateBuiltinVideoDecoderFactory(),
                nullptr,
                nullptr);

    // 创建PeerConnection的配置
    webrtc::PeerConnectionInterface::RTCConfiguration config;
    // ...配置STUN/TURN服务器等
    webrtc::PeerConnectionInterface::IceServer server;
    config.servers.push_back(server);
    // 创建PeerConnection
    _peer_connection = _peer_connection_factory->CreatePeerConnection(
                config, nullptr, nullptr, nullptr);

    rtc::scoped_refptr<webrtc::AudioTrackInterface> audio_track(
                _peer_connection_factory->CreateAudioTrack(
                    "audio_label", _peer_connection_factory->CreateAudioSource(
                        cricket::AudioOptions())));
    _peer_connection->AddTrack(audio_track, {"stream_id"});
    //
    rtc::scoped_refptr<webrtc::VideoTrackInterface> video_track_(
             _peer_connection_factory->CreateVideoTrack("video_label",
                                                        CapturerTrackSource::Create()));;
    _peer_connection->AddTrack(video_track_, {"stream_id"});
}
