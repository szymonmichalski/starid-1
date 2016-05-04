TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = base

SOURCES += \
    catalog.cpp \
    sensor.cpp \
    base.cpp \
    pointing.cpp

HEADERS += \
    catalog.h \
    sensor.h \
    pointing.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so


