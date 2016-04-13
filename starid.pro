TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    catalog.cpp \
    indexfinder.cpp \
    starpairs.cpp \
    sensor.cpp \
    base.cpp

HEADERS += \
    catalog.h \
    indexfinder.h \
    starpairs.h \
    sensor.h \
    base.h

DISTFILES += \
    LICENSE.txt \
    README.md
