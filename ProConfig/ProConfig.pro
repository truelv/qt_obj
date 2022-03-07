#-------------------------------------------------
#
# Project created by QtCreator 2022-03-06T21:55:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProConfig
TEMPLATE = app

# 这里选择不同的编译模式 test 1 2 3
CONFIG += test2

test1
{
DEFINES += TEST_TYPE=1
}
test2
{
DEFINES += TEST_TYPE=2
}


    SOURCES += main.cpp\
        mainwindow.cpp
test1{
    SOURCES += test1.cpp
}test2{
    SOURCES += test2.cpp
}test3{
    SOURCES += test3.cpp
}

HEADERS  += mainwindow.h \
    test1.h \
    test2.h \
    test3.h

FORMS    += mainwindow.ui
