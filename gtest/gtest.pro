TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = gtest

SOURCES += \
    gtest.cpp \
    gtest_geometry.cpp

HEADERS += \

INCLUDEPATH += ../base
LIBS += ../base/geometry.o

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so




