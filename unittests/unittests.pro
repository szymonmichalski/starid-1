TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

TARGET = unittests

SOURCES += \
    unittests.cpp \
    base_pointing.cpp \
    ptq_main.cpp \
    base_main.cpp

HEADERS += \

INCLUDEPATH += ../base
LIBS += ../base/pointing.o
LIBS += ../base/catalog.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../ptq
LIBS += ../ptq/pairs.o
LIBS += ../ptq/triplets.o

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





