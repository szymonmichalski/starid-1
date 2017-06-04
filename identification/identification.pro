TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = identification

DIR=/home/noah/starid
include($$DIR/stars/stars.pri)
include($$DIR/identification/identification.pri)
INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/libstarid

SOURCES += identification.cpp
