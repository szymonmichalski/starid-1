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
    $$DIR/stars/globals.cpp \
    $$DIR/stars/sky.cpp \

HEADERS += \
    $$DIR/stars/globals.h \
    $$DIR/stars/sky.h \

SOURCES += \
    $$DIR/identification/triangles.cpp \

HEADERS += \
    $$DIR/identification/triangles.h \
