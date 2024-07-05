#include <QDebug>
#include "localcamera.h"
#include "ui_localcamera.h"
#include "rtc_base/synchronization/mutex.h"
#include "api/video/i420_buffer.h"
#include "common_video/libyuv/include/webrtc_libyuv.h"

LocalCamera::LocalCamera(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalCamera)
{
    ui->setupUi(this);
    getDeviceList();

    _vback = new VideoCallback(_showImage);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(updateImage()));
}

LocalCamera::~LocalCamera()
{
    delete ui;
}

void LocalCamera::on_open_cam_clicked()
{
    webrtc::VideoCaptureModule::DeviceInfo
            *device_info_ = webrtc::VideoCaptureFactory::CreateDeviceInfo();
    char device_name[256];
    char unique_name[256];
    if(device_info_->GetDeviceName(ui->list_cam->currentIndex(), device_name, 256,
                                   unique_name, 256) !=0)
    {
        qDebug()<<"info->GetDeviceName error";
        return ;
    }

    // 创建采集模块
    _module = webrtc::VideoCaptureFactory::Create(unique_name);
    if (_module.get() == NULL)
    {
        qDebug()<<"webrtc::VideoCaptureFactory::Create error";
        return ;
    }

    _module->RegisterCaptureDataCallback(_vback);
    device_info_->GetCapability(_module->CurrentDeviceName(), 0, _capability);

    // 打开摄像头
    if(_module->StartCapture(_capability)!=0)
    {
        qDebug()<<"m_module->StartCapture failed";
        return;
    }

    if(_module->CaptureStarted())
    {
        qDebug()<<"Capture is running";
    }

    //m_timer.start(40);
    ui->open_cam->setText(tr("关闭"));

    _timer.start(40);
}

void LocalCamera::updateImage()
{
    ui->show_cam->setPixmap(QPixmap::fromImage(_showImage));
}

void LocalCamera::getDeviceList()
{
    webrtc::VideoCaptureModule::DeviceInfo
            *info = webrtc::VideoCaptureFactory::CreateDeviceInfo();
    int deviceNum = info->NumberOfDevices();

    for (int i = 0; i < deviceNum; ++i)
    {
        const uint32_t kSize = 256;
        char name[kSize] = {0};
        char id[kSize] = {0};
        if (info->GetDeviceName(i, name, kSize, id, kSize) != -1)
        {
            ui->list_cam->addItem(QString(name));
        }
    }

    if(deviceNum==0)
    {
        ui->open_cam->setEnabled(false);
    }
}

#include "third_party/libyuv/include/libyuv.h"

LocalCamera::VideoCallback::VideoCallback(QImage &img) :
    _img(img)
{

}

void LocalCamera::VideoCallback::OnFrame(const webrtc::VideoFrame &videoFrame)
{
    //webrtc::MutexLock lock(&capture_lock_);
    int height = videoFrame.height();
    int width = videoFrame.width();
    _incoming_frames++;
    qDebug()<<"width"<<width<<"height"<<height<<"incoming_frames_"<< _incoming_frames;

//将收到的数据帧转换下格式
    rtc::scoped_refptr<webrtc::I420BufferInterface> buffer(
        videoFrame.video_frame_buffer()->ToI420());
//开辟一段存放BGR数据的空间
    const int length =buffer->width()* buffer->height()*3;
    qDebug()<<"buffer->width()"<<buffer->width()<<"buffer->height()"<<buffer->height();
    uchar *imageBuffer=new uchar[length];

//使用libyuvy库转换一帧数据到BGR
    libyuv::I420ToRGB24(buffer->DataY(), buffer->StrideY(), buffer->DataU(),
                       buffer->StrideU(), buffer->DataV(), buffer->StrideV(),
                       imageBuffer,
                       buffer->width()*3,
                       buffer->width(), buffer->height());
//将得到的数据放入QImage中
    QImage image(imageBuffer, buffer->width(), buffer->height(), QImage::Format_RGB888);
    qDebug()<<image;
    _img=image.copy();
    delete imageBuffer;
}
