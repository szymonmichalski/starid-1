include (../stars/stars.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = gtest

HEADERS += \

SOURCES += \
    gtest_main.cpp \
    tests1.cpp

INCLUDEPATH += ../../gtest/include
LIBS += ../../gtest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





