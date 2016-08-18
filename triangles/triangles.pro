include (../stars/stars.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = triangles

SOURCES += \
    pairs.cpp \
    triangles_main.cpp \
    triangles.cpp

HEADERS += \
    pairs.h \
    triangles.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
#    pairs.pri

