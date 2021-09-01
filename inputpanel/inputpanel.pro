SOURCES += main.cpp \
           myinputpanel.cpp \
           myinputpanelcontext.cpp

HEADERS += myinputpanel.h \
           myinputpanelcontext.h

FORMS   += mainform.ui \
           myinputpanelform.ui


#LIBS += -L/home/zhh/work/qt_obj/inputpanel/sdk/lib \
#    -lpthread -lm -lts -lz -ljpeg -lpng -lfreetype -lssl -lcrypto -lopencv_core \
#    -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -lopencv_videoio -lopencv_calib3d \
#    -lopencv_features2d -lopencv_flann -ljasper -lopencv_ml -ltinyalsa -lasound\
#    -lface_svc -liniparser -lxlsreader -lxlsxwriter -lxlswriter \
#    -llombo_malloc -lomx_arender -lrecorder -ldrm -lomx -llombo_jpeg -lvideo -laudio -lqrencode -lflip -lzbar \
#    -lnet_utils -lethernet -lwifi_station -lwpa_client -lwifi_softap -lsys_sound -lent_wechat -lgattimpl \
#    -ldtbased_tk -lnn_engine -lopenvx -lopenvx-nn -lnn-priv -lnn -lsoft-nn -llog -lcut -lliving -lnirdt \
#    -ltts-16k


# install
target.path = $$[QT_INSTALL_EXAMPLES]/tools/inputpanel
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS inputpanel.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/tools/inputpanel
INSTALLS += target sources

symbian: include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

symbian: warning(This example might not fully work on Symbian platform)
maemo5: warning(This example might not fully work on Maemo platform)
simulator: warning(This example might not fully work on Simulator platform)
