TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = stars

DIR=/home/noah/starid
include($$DIR/star/star.pri)
INCLUDEPATH += \
    $$DIR/star \
    $$DIR/lib

SOURCES += stars.cpp
