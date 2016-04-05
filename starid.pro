TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    catalog.cpp \
    indexfinder.cpp \
    starpairs.cpp \
    util.cpp

HEADERS += \
    catalog.h \
    indexfinder.h \
    util.h \
    starpairs.h \
    sensor.h

DISTFILES += \
    LICENSE.txt \
    README.md
