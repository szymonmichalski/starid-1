TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = gtest

SOURCES += \
    gtest.cpp \
    gtest_geometry.cpp

HEADERS += \

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/make/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

LIBS += ../base/geometry.o




