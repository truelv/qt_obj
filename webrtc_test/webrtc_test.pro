#-------------------------------------------------
#
# Project created by QtCreator 2024-03-19T09:07:35
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = webrtc_test
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
##
# linux plat
DEFINES += WEBRTC_POSIX
#DEFINES += HAVE_WEBRTC_VOICE  WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE \
#    WEBRTC_USE_H264 WEBRTC_INITIALIZE_FFMPEG  FFMPEG_H264_DECODER
DEFINES += QT_NO_KEYWORDS
#
#DEFINES += WEBRTC_EXTERNAL_JSON



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14 console

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rtcmanager.cpp \
    localcamera.cpp \
    rmotecamera.cpp \
    serverconnect.cpp \
    base/jsonlibC/cJSON.c \
    rtppeerconnect.cpp \
    base/rtc/vcm_capturer.cc \
    base/rtc/test_video_capturer.cc \
    base/rtc/video_track_source.cc \
    serverconnectbase.cpp

HEADERS += \
        mainwindow.h \
    rtcmanager.h \
    localcamera.h \
    rmotecamera.h \
    serverconnect.h \
    base/jsonlibC/cJSON.h \
    rtppeerconnect.h \
    serverconnectbase.h

FORMS += \
        mainwindow.ui \
    localcamera.ui \
    rmotecamera.ui

INCLUDEPATH += base/jsonlibC \
    base/rtc \
    base/rtc/third_party/abseil-cpp \
    base/rtc/third_party/libyuv/include \
    base/rtc/third_party/protobuf/conformance/third_party \
    base/rtc/build/linux/debian_sid_amd64-sysroot/usr/include/jsoncpp



unix:!macx: LIBS += -L$$PWD/base/rtc/ -lwebrtc
#INCLUDEPATH += $$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj
#DEPENDPATH += $$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj
unix:!macx: PRE_TARGETDEPS += $$PWD/base/rtc/libwebrtc.a

unix:!macx: LIBS += -L$$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu/ -ldl -lX11
#INCLUDEPATH += $$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu
#DEPENDPATH += $$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu
