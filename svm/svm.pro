include (../stars/stars.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = svm

SOURCES += \
    model.cpp \
    train.cpp \
    knntrain.cpp \
    svm_main.cpp

HEADERS += \
    model.h \
    train.h \
    knntrain.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    svm.pri

