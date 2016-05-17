TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = base

SOURCES += \
    catalog.cpp \
    sensor.cpp \
    pointing.cpp \
    main.cpp \
    training.cpp

HEADERS += \
    catalog.h \
    sensor.h \
    pointing.h \
    training.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so


