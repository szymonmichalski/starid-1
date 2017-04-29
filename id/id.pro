TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = id

DIR=/home/noah/starid
include($$DIR/stars/stars.pri)
include($$DIR/id/id.pri)
INCLUDEPATH += ../stars

SOURCES += id.cpp
