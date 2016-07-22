include (../base/base.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = convnet

SOURCES += \
    mnist.cpp \
    convnet_main.cpp

HEADERS += \
    mnist.h


INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    convnet.py \
    convnet_input.py \
    convnet_train.py
