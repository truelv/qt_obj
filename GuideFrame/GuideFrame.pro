#-------------------------------------------------
#
# Project created by QtCreator 2021-12-28T09:36:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GuideFrame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    guideframe.cpp \
    stepWin/ethsetting.cpp \
    stepWin/base/selectwin.cpp \
    guideconf.cpp \
    stepWin/contrlmode.cpp \
    stepWin/authmode.cpp \
    stepWin/serverip.cpp \
    stepWin/serverurl.cpp \
    stepWin/base/inputkvs.cpp \
    stepWin/doorandcontrlnum.cpp

HEADERS  += mainwindow.h \
    guideframe.h \
    stepWin/ethsetting.h \
    stepWin/base/selectwin.h \
    guideconf.h \
    stepWin/contrlmode.h \
    stepWin/authmode.h \
    stepWin/serverip.h \
    stepWin/serverurl.h \
    stepWin/base/inputkvs.h \
    stepWin/doorandcontrlnum.h \
    stepWin/base/ifacechildopt.h

FORMS    += mainwindow.ui \
    guideframe.ui \
    stepWin/ethsetting.ui \



LIBS += -L/home/zhh/work/052_YT328智通终端/01.开发库/050.软件开发/020.源代码/ZYTK_Reader_YT328/sdk/lib \
    -lpthread -lm -lts -lz -ljpeg -lpng -lfreetype -lssl -lcrypto -lopencv_core \
    -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_calib3d \
    -lopencv_features2d -lopencv_flann -ljasper -lopencv_ml -ltinyalsa -lasound\
    -lface_svc -liniparser -lxlsreader -lxlsxwriter -lxlswriter \
    -llombo_malloc -lomx_arender -lrecorder -ldrm -lomx -llombo_jpeg -lvideo -laudio -lqrencode -lflip -lzbar \
    -lnet_utils -lethernet -lwifi_station -lwpa_client -lwifi_softap -lsys_sound -lent_wechat -lgattimpl \
    -ldtbased_tk -lnn_engine -lopenvx -lopenvx-nn -lnn-priv -lnn -lsoft-nn -llog -lcut -lliving -lnirdt \


