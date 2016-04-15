TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = base

SOURCES += \
    catalog.cpp \
    indexfinder.cpp \
    sensor.cpp \
    starpairs.cpp \
    geometry.cpp \
    base.cpp

HEADERS += \
    catalog.h \
    indexfinder.h \
    sensor.h \
    starpairs.h \
    geometry.h

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/make/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so
