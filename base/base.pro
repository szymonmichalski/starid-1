TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = base

SOURCES += \
    catalog.cpp \
    indexfinder.cpp \
    sensor.cpp \
    geometry.cpp \
    base.cpp

HEADERS += \
    catalog.h \
    indexfinder.h \
    sensor.h \
    geometry.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so


