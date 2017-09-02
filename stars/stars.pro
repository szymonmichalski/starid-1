TEMPLATE = app
TARGET = stars
CONFIG = c++14 warn_on debug
CONFIG -= qt

SOURCES += stars.cpp

DIR=/home/noah/starid
INCLUDEPATH += $$DIR/lib
INCLUDEPATH += $$DIR/libstarid
INCLUDEPATH += $$DIR/stars
INCLUDEPATH += $$DIR/identification
HEADERS += $$DIR/libstarid/globals.h
SOURCES += $$DIR/libstarid/globals.cpp
HEADERS += $$DIR/stars/sky.h
SOURCES += $$DIR/stars/sky.cpp
HEADERS += $$DIR/identification/triangles.h
SOURCES += $$DIR/identification/triangles.cpp

DISTFILES += \
    CMakeLists.txt
