TARGET = starid
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug

DIR=/home/noah/starid
include($$DIR/stars/star.pri)
include($$DIR/identification/identification.pri)
INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/identification \
    $$DIR/lib \
    /usr/include/python3.5m \

SOURCES += libstarid.cpp
HEADERS += libstarid.h

