TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = base

SOURCES += \
    catalog.cpp \
    sensor.cpp \
    pointing.cpp \
    training.cpp \
    base_main.cpp

HEADERS += \
    catalog.h \
    sensor.h \
    pointing.h \
    training.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    base.pri


