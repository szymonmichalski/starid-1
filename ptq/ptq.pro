TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = ptq

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
    triplets.cpp \
    pairs.cpp \
    main.cpp

HEADERS += \
    $$DIR1/catalog.h \
    $$DIR1/pointing.h \
    $$DIR1/sensor.h \
    $$DIR1/training.h \
    triplets.h \
    pairs.h

INCLUDEPATH += ../base
LIBS += ../base/pointing.o
LIBS += ../base/catalog.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

