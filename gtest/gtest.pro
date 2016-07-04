include (../base/base.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = gtest

HEADERS += \

SOURCES += \
    main.cpp \
    base.cpp

INCLUDEPATH += ../../gtest/include
LIBS += ../../gtest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





