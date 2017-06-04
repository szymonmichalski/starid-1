TEMPLATE = app
TARGET = stars
CONFIG = c++14 warn_on debug
CONFIG -= qt

DIR=/home/noah/starid

INCLUDEPATH += \
    $$DIR/identification \
    $$DIR/libstarid

SOURCES += stars.cpp

SOURCES += \
    $$DIR/stars/globals.cpp \
    $$DIR/stars/sky.cpp \

HEADERS += \
    $$DIR/stars/globals.h \
    $$DIR/stars/sky.h \

SOURCES += \
    $$DIR/identification/triangles.cpp \

HEADERS += \
    $$DIR/identification/triangles.h \
