TEMPLATE = app
TARGET = identification
CONFIG = c++14 warn_off debug
CONFIG -= qt

DIR=/home/noah/starid

INCLUDEPATH += \
    $$DIR/stars \
    $$DIR/libstarid

SOURCES += identification.cpp

SOURCES += \
    $$DIR/identification/triangles.cpp \

HEADERS += \
    $$DIR/identification/triangles.h \

SOURCES += \
    $$DIR/stars/globals.cpp \
    $$DIR/stars/sky.cpp \

HEADERS += \
    $$DIR/stars/globals.h \
    $$DIR/stars/sky.h \

