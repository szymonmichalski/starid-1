include (../base/base.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = knn

SOURCES += \
    knntrain.cpp \
    main.cpp

HEADERS += \
    knntrain.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    knn.pri
