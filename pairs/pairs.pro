include (../base/base.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = pairs

SOURCES += \
    triplets.cpp \
    pairs.cpp \
    pairs_main.cpp

HEADERS += \
    triplets.h \
    pairs.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    pairs.pri

