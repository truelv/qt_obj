#-------------------------------------------------
#
# Project created by QtCreator 2021-07-30T01:01:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_thread
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testthreadtype1.cpp \
    testthreadtype2.cpp

HEADERS  += mainwindow.h \
    testthreadtype1.h \
    testthreadtype2.h

FORMS    += mainwindow.ui
