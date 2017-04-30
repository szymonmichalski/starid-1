TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = stars

DIR=/home/noah/starid
include($$DIR/stars/stars.pri)
INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/lib

SOURCES += stars.cpp
