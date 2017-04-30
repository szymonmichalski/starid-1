TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = id

DIR=/home/noah/starid
include($$DIR/star/star.pri)
include($$DIR/identification/identification.pri)
INCLUDEPATH += \
    $$DIR/star \
    $$DIR/lib

SOURCES += id.cpp
