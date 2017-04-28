TARGET = starid
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug

DIR=/home/noah/starid
include($$DIR/stars/stars.pri)
include($$DIR/id/id.pri)
INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/id \
    $$DIR/stars/Eigen \
    /usr/include/python3.5m \

SOURCES += libstarid.cpp
HEADERS += libstarid.h

