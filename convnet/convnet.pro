include (../base/base.pri)
include (../svm/svm.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = svmtf

SOURCES += \
    main.cpp

HEADERS += \


INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    cifar10_input.py \
    cifar10.py \
    cifar10_train.py \
    cifar10_multi_gpu_train.py \
    cifar10_eval.py \
    mnist.py
