QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

#QMAKE_LFLAGS += /MANIFESTUAC:\"level=\'requireAdministrator\' uiAccess=\'false\'\"
# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(modTelnet/qttelnet.pri)

SOURCES += \
    devselect.cpp \
    item/checkboxinwidget.cpp \
    main.cpp \
    mainwindow.cpp \
    api\deviceInfo.cpp \
    base\tcpIp\multicast.c \
    base\tcpIp\socket_file.c \
    base\tcpIp\raw_socket.c \
    base\dstruct\linkedlist\linkedlist.c \
    base\core\task_core.c \
    mainwindow2.cpp \
    protocol/device_prot.c \
    servers/cftp.cpp \
    servers/sbase.cpp \
    servers/serversmanager.cpp \
    servers/stftpd.cpp \
    servers/telnet/telnetsv.cpp

HEADERS += \
    devselect.h \
    item/checkboxinwidget.h \
    mainwindow.h \
    api\deviceInfo.h \
    base\tcpIp\multicast.h \
    base\tcpIp\socket_file.h \
    base\tcpIp\raw_socket.h \
    base\tcpIp\tcpIp_errno.h \
    base\dstruct\linkedlist\linkedlist.h \
    base\core\task_core.h \
    base\core\task_core_error.h \
    mainwindow2.h \
    protocol/device_prot.h \
    servers/cftp.h \
    servers/sbase.h \
    servers/serversmanager.h \
    servers/stftpd.h \
    servers/telnet/telnetsv.h

FORMS += \
    devselect.ui \
    mainwindow.ui \
    mainwindow2.ui

INCLUDEPATH += \
    api protocol base\dstruct

TRANSLATIONS += \
    WinTools_zh_CN.ts

LIBS += \
    libwsock32 libws2_32

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
