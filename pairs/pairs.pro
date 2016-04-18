TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = pairs

SOURCES += \
    pairs.cpp \
    angles.cpp

HEADERS += \
    angles.h

INCLUDEPATH += ../base
LIBS += ../base/geometry.o
LIBS += ../base/catalog.o
LIBS += ../base/indexfinder.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

