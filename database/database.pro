#-------------------------------------------------
#
# Project created by QtCreator 2021-06-12T22:42:30
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = database
TEMPLATE = app


SOURCES += main.cpp\
        database/testsqlite3.cpp \
    qt_ui/listdatabaseview.cpp \
    database/systeminfo.cpp \
    database/lineitem.cpp \
    qt_ui/testscreenpush.cpp \
    qt_ui/uicontroler.cpp \
    qt_ui/login.cpp

HEADERS  += \
    qt_ui/listdatabaseview.h \
    qt_ui/testscreenpush.h \
    qt_ui/uicontroler.h \
    qt_ui/login.h

INCLUDEPATH += database/include \
    qt_ui \

FORMS    += \
    qt_ui/listdatabaseview.ui \
    qt_ui/testscreenpush.ui \
    qt_ui/login.ui
