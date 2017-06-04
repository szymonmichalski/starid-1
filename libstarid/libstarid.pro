TEMPLATE = lib
TARGET = starid
CONFIG += c++14 warn_off debug
CONFIG -= qt

DIR=/home/noah/starid

INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/identification \
    $$DIR/libstarid \
    /usr/include/python3.5m \

SOURCES += libstarid.cpp

HEADERS += libstarid.h

SOURCES += \
    $$DIR/libstarid/globals.cpp \
    $$DIR/stars/sky.cpp \
    $$DIR/identification/triangles.cpp \

HEADERS += \
    $$DIR/libstarid/globals.h \
    $$DIR/stars/sky.h \
    $$DIR/identification/triangles.h \

