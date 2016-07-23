TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = stars

SOURCES += \
    catalog.cpp \
    sensor.cpp \
    pointing.cpp \
    stars_main.cpp \
    mnist.cpp

HEADERS += \
    catalog.h \
    sensor.h \
    pointing.h \
    mnist.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    stars.pri \
    mnist_to_tfrecords.py \


