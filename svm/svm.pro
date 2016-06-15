TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = svm

SOURCES += \
    main.cpp \
    svmtrain.cpp \
    solver.cpp

HEADERS += \
    svmtrain.h \
    solver.h

INCLUDEPATH += ../base
LIBS += ../base/pointing.o
LIBS += ../base/catalog.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so
