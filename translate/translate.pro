#-------------------------------------------------
#
# Project created by QtCreator 2021-07-10T23:54:17
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = translate
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui


TRANSLATIONS += English.ts\
                Chinese.ts\
                Japanese.ts

RESOURCES += \
    res.qrc
