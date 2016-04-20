TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = gtest

SOURCES += \
    gtest.cpp \
    gtest_geometry.cpp \
    gtest_base.cpp

HEADERS += \

INCLUDEPATH += ../base
LIBS += ../base/geometry.o
LIBS += ../base/catalog.o
LIBS += ../base/indexfinder.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





