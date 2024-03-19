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
DEFINES += HAVE_WEBRTC_VOICE  WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE \
    WEBRTC_USE_H264 WEBRTC_INITIALIZE_FFMPEG  FFMPEG_H264_DECODER  WEBRTC_POSIX
DEFINES += QT_DEPRECATED_WARNINGS QT_NO_KEYWORDS



# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#CONFIG += c++11 console

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    rtcmanager.cpp

HEADERS += \
        mainwindow.h \
    rtcmanager.h

FORMS += \
        mainwindow.ui

INCLUDEPATH += /home/zhh/work/video/webrtc/webrtc/src \
    += /home/zhh/work/video/webrtc/webrtc/src/third_party/abseil-cpp


