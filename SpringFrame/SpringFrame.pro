#-------------------------------------------------
#
# Project created by QtCreator 2021-12-23T15:04:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpringFrame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    springframe.cpp \
    interUi/interui.cpp \
    interUi/sflinetext.cpp \
    interUi/sfinputline.cpp \
    interUi/sf485error.cpp

HEADERS  += mainwindow.h \
    springframe.h \
    interUi/interui.h \
    interUi/sflinetext.h \
    interUi/sfinputline.h \
    interUi/sf485error.h

FORMS    += mainwindow.ui \
    springframe.ui \
    interUi/messagelinetext.ui \
    interUi/inputline.ui \
    interUi/sf485error.ui


LIBS += -L/home/zhh/work/052_YT328智通终端/01.开发库/050.软件开发/020.源代码/ZYTK_Reader_YT328/sdk/lib \
    -lpthread -lm -lts -lz -ljpeg -lpng -lfreetype -lssl -lcrypto -lopencv_core \
    -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_calib3d \
    -lopencv_features2d -lopencv_flann -ljasper -lopencv_ml -ltinyalsa -lasound\
    -lface_svc -liniparser -lxlsreader -lxlsxwriter -lxlswriter \
    -llombo_malloc -lomx_arender -lrecorder -ldrm -lomx -llombo_jpeg -lvideo -laudio -lqrencode -lflip -lzbar \
    -lnet_utils -lethernet -lwifi_station -lwpa_client -lwifi_softap -lsys_sound -lent_wechat -lgattimpl \
    -ldtbased_tk -lnn_engine -lopenvx -lopenvx-nn -lnn-priv -lnn -lsoft-nn -llog -lcut -lliving -lnirdt \
