#-------------------------------------------------
#
# Project created by QtCreator 2018-07-20T10:09:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RectTest
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

MOC_DIR = ./tmp
RCC_DIR = ./tmp
UI_DIR = ./tmp
OBJECTS_DIR = ./tmp

Debug:DESTDIR= ./bin/debug
Release:DESTDIR = ./bin/release


#Debug:LIBS += ../../../bin/debug/VisionCamera.lib
#Release:LIBS += ../../../bin/release/VisionCamera.lib

LIBS += ./lib/XVCreateRegion.lib


INCLUDEPATH += ./include/XVCore

SOURCES += main.cpp\
        mainwindow.cpp \
    visionellipseitem.cpp \
    visionitem.cpp \
    visionrectitem.cpp \
    visionrectitem_rotate.cpp \
    minirect.cpp \
    visionarrows_rotate.cpp \
    visionring.cpp \
    visionrectitem_new.cpp \
    visionellipseitem_new.cpp \
    visionlineitem.cpp \
    visionwidgetitem.cpp \
    visiongraphscene.cpp \
    visiongraphview.cpp \
    visionpolygon.cpp \
    visionpathitem.cpp \
    lineitem.cpp \
    visionpoint.cpp

HEADERS  += mainwindow.h \
    visionellipseitem.h \
    visionitem.h \
    visionrectitem.h \
    visionrectitem_rotate.h \
    minirect.h \
    visionarrows_rotate.h \
    visionring.h \
    visionrectitem_new.h \
    visionellipseitem_new.h \
    visionlineitem.h \
    visionwidgetitem.h \
    visiongraphscene.h \
    visiongraphview.h \
    visionpolygon.h \
    visionpathitem.h \
    lineitem.h \
    visionpoint.h

RESOURCES += \
    image.qrc
