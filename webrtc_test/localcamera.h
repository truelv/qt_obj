#ifndef LOCALCAMERA_H
#define LOCALCAMERA_H
#include <QWidget>
#include <QTimer>
#include "modules/video_capture/video_capture.h"
#include "modules/video_capture/video_capture_factory.h"
#if 1
#include "api/video/video_sink_interface.h"
#include "api/media_stream_interface.h"
#include "api/scoped_refptr.h"
#endif
#include "modules/video_capture/video_capture_factory.h"
#include "modules/video_capture/video_capture.h"
#include "api/video/video_sink_interface.h"
#include "api/video/video_frame.h"

namespace Ui {
class LocalCamera;
}

class LocalCamera : public QWidget
{
    Q_OBJECT

public:
    explicit LocalCamera(QWidget *parent = 0);
    ~LocalCamera();

private Q_SLOTS:
    void on_open_cam_clicked();
    void updateImage();

private:
    void getDeviceList();

private:
    QTimer _timer;
    QImage _showImage;

    Ui::LocalCamera *ui;
    // 采集模块
    rtc::scoped_refptr<webrtc::VideoCaptureModule> _module;
    // VideoCaptureCapability 摄像头参数
    webrtc::VideoCaptureCapability _capability;

    class VideoCallback : public rtc::VideoSinkInterface<webrtc::VideoFrame> {
    public:
        VideoCallback(QImage& img);
        void OnFrame(const webrtc::VideoFrame& frame);
        QImage& _img;
    private:
        unsigned int _incoming_frames;

    };
    VideoCallback* _vback;
};
#endif // LOCALCAMERA_H
