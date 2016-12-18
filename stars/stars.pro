TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = stars

SOURCES += \
    sensor.cpp \
    stars_main.cpp \
    mnist.cpp \
    stars.cpp \
    float_int_table.cpp

HEADERS += \
    sensor.h \
    mnist.h \
    stars.h \
    float_int_table.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    stars.pri \


