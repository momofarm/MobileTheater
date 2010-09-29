#-------------------------------------------------
#
# Project created by QtCreator 2010-09-19T17:22:15
#
#-------------------------------------------------

QT       += core gui network

TARGET = phonetheater
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    QSelectByArea.cpp \
    httpTool.cpp \
    QTheaterList.cpp \
    QAreaList.cpp \
    QSelectByTheater.cpp \
    qtimetable.cpp \
    qlistmodel.cpp \
    listviewitem.cpp \
    todayshow.cpp \
    QGpsList.cpp

HEADERS  += mainwindow.h \
    QSelectByArea.h \
    httpTool.h \
    QUrlFactory.h \
    Constants.h \
    QTheaterList.h \
    QAreaList.h \
    QSelectByTheater.h \
    qtimetable.h \
    qlistmodel.h \
    listviewitem.h \
    todayshow.h \
    QGPSList.h

FORMS    += mainwindow.ui

CONFIG += mobility

LIBS += -Lc:/s60prj/qjson/lib -lqjson
INCLUDEPATH += c:/s60prj/qjson/src

MOBILITY = location

symbian {
    TARGET.UID3 = 0xe02cf031
    # TARGET.CAPABILITY += 
    TARGET.EPOCSTACKSIZE = 0x14000
    TARGET.EPOCHEAPSIZE = 0x020000 0x800000
}
