TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = ptq

SOURCES += \
    triplets.cpp \
    pairs.cpp \
    main.cpp

HEADERS += \
    triplets.h \
    pairs.h

INCLUDEPATH += ../base
LIBS += ../base/pointing.o
LIBS += ../base/catalog.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

