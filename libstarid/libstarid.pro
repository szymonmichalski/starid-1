TARGET = starid
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug

DIR=/home/noah/starid
include($$DIR/star/star.pri)
include($$DIR/identification/identification.pri)
INCLUDEPATH += \
    $$DIR/star \
    $$DIR/identification \
    $$DIR/lib \
    /usr/include/python3.5m \

SOURCES += libstarid.cpp
HEADERS += libstarid.h

