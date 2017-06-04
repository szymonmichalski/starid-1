TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = stars

DIR=/home/noah/starid
include($$DIR/stars/stars.pri)
include($$DIR/identification/identification.pri)
INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/identification \
    $$DIR/libstarid

SOURCES += stars.cpp
