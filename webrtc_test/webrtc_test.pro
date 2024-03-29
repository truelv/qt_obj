#-------------------------------------------------
#
# Project created by QtCreator 2024-03-19T09:07:35
#
#-------------------------------------------------

QT       += core gui

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



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14 console

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rtcmanager.cpp \
    localcamera.cpp

HEADERS += \
        mainwindow.h \
    rtcmanager.h \
    localcamera.h

FORMS += \
        mainwindow.ui \
    localcamera.ui

INCLUDEPATH += /media/cp/1f4ae5c9-7b98-4e3d-b846-2a0bd3c8cfa2/home/zhh/work/video/webrtc/webrtc/src \
     /media/cp/1f4ae5c9-7b98-4e3d-b846-2a0bd3c8cfa2/home/zhh/work/video/webrtc/webrtc/src/third_party/abseil-cpp \
     /media/cp/1f4ae5c9-7b98-4e3d-b846-2a0bd3c8cfa2/home/zhh/work/video/webrtc/webrtc/src/third_party/libyuv/include



unix:!macx: LIBS += -L$$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj/ -lwebrtc
#INCLUDEPATH += $$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj
#DEPENDPATH += $$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj
unix:!macx: PRE_TARGETDEPS += $$PWD/../../video/webrtc/webrtc/src/out/linux_x64_g++_release/obj/libwebrtc.a

unix:!macx: LIBS += -L$$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu/ -ldl -lX11
#INCLUDEPATH += $$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu
#DEPENDPATH += $$PWD/../../../../../../../../usr/lib/x86_64-linux-gnu
