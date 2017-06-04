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
    $$DIR/libstarid/globals.cpp \
    $$DIR/stars/sky.cpp \
    $$DIR/identification/triangles.cpp \

HEADERS += \
    $$DIR/libstarid/globals.h \
    $$DIR/stars/sky.h \
    $$DIR/identification/triangles.h \

