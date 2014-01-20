#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T17:21:11
#
#-------------------------------------------------

QT       -= gui

TARGET = LGLReader
TEMPLATE = lib
CONFIG += staticlib C++11

SOURCES += \
    libaction.cpp \
    libargument.cpp \
    library.cpp \
    libmanager.cpp

HEADERS += \
    libaction.h \
    libargument.h \
    library.h \
    libmanager.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
