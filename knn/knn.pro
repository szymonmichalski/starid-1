TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = knn

DIR1 = ../base
DIR2 = ../ptq
DIR3 = ../knn
DIR4 = ../svm
INCLUDEPATH += $$DIR1
INCLUDEPATH += $$DIR2
INCLUDEPATH += $$DIR3
INCLUDEPATH += $$DIR4

SOURCES += \
    $$DIR1/catalog.cpp \
    $$DIR1/pointing.cpp \
    $$DIR1/sensor.cpp \
    $$DIR1/training.cpp \
    knntrain.cpp \
    main.cpp

HEADERS += \
    $$DIR1/catalog.h \
    $$DIR1/pointing.h \
    $$DIR1/sensor.h \
    $$DIR1/training.h \

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

HEADERS += \
    knntrain.h
