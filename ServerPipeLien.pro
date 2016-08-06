#-------------------------------------------------
#
# Project created by QtCreator 2016-08-01T11:33:50
#
#-------------------------------------------------

QT       += core gui network
unix:QMAKE_CXXFLAGS += -std=c++11
win32-g++: QMAKE_CXXFLAGS += -std=c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ServerPipeLien
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    logger/st_logger.cpp \
    network/zp_net_threadpool.cpp \
    network/zp_netlistenthread.cpp \
    network/zp_nettransthread.cpp \
    network/zp_tcpclient.cpp \
    network/zp_tcpserver.cpp \
    pipeline/zp_pipeline.cpp \
    pipeline/zp_pltaskbase.cpp \
    pipeline/zp_plworkingthread.cpp \
    cluster/zp_clusternode.cpp \
    cluster/zp_clusterterm.cpp

HEADERS  += mainwindow.h \
    logger/st_logger.h \
    network/zp_net_threadpool.h \
    network/zp_netlistenthread.h \
    network/zp_nettransthread.h \
    network/zp_tcpclient.h \
    network/zp_tcpserver.h \
    pipeline/zp_pipeline.h \
    pipeline/zp_pltaskbase.h \
    pipeline/zp_plworkingthread.h \
    cluster/cross_svr_messages.h \
    cluster/zp_clusternode.h \
    cluster/zp_clusterterm.h

FORMS    += mainwindow.ui

CONFIG+=debug_and_release
CONFIG(debug,debug|release)
{
unix:TARGET=$$join(TARGET,,,_debug)
win32:TARGET=$$join(TARGET,,,d)
}

MOC_DIR = temp/moc
OBJECTS_DIR = temp/obj
UI_HEADERS_DIR = temp/ui
RCC_DIR = temp/rcc
DESTDIR = temp/bin
