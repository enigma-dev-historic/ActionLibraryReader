#-------------------------------------------------
#
# Project created by QtCreator 2014-01-20T17:21:11
#
#-------------------------------------------------

QT       -= gui

TARGET = LGLReader
TEMPLATE = lib
CONFIG += staticlib C++11

INCLUDEPATH += include/

SOURCES += \
    src/libaction.cpp \
    src/libargument.cpp \
    src/library.cpp \
    src/libmanager.cpp

HEADERS += \
    include/libaction.h \
    include/libargument.h \
    include/library.h \
    include/libmanager.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
