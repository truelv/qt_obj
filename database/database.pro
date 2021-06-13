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
    database/lineitem.cpp

HEADERS  += \
    qt_ui/listdatabaseview.h \

INCLUDEPATH += database/include \
    qt_ui \

FORMS    += \
    qt_ui/listdatabaseview.ui
