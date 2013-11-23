#-------------------------------------------------
#
# Project created by QtCreator 2013-07-26T10:10:05
#
#-------------------------------------------------

# Qt Modules
QT       += network

QT       -= gui

# Project Information
TARGET = TaskScheduler
TEMPLATE = lib

QMAKE_CXXFLAGS += -std=c++11

# Project Files
DEFINES += TASKSCHEDULER_LIBRARY

HEADERS += \
    task.h \
    taskpoolworker.h \
    taskpool.h \
    internal/taskpooldata.h

SOURCES += \
    taskpool.cpp

