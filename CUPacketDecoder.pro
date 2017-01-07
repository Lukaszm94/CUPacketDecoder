#-------------------------------------------------
#
# Project created by QtCreator 2017-01-06T14:09:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets serialport

CONFIG += c++11

TARGET = CUPacketDecoder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    serialmanager.cpp \
    packetparser.cpp \
    application.cpp \
    buffer.cpp \
    gui.cpp \
    datamanager.cpp \
    logwidget.cpp \
    lightswidget.cpp

HEADERS  += mainwindow.h \
    serialmanager.h \
    packetparser.h \
    datatypes.h \
    application.h \
    buffer.h \
    gui.h \
    datamanager.h \
    logwidget.h \
    lightswidget.h
