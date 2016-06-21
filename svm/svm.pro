include (../base/base.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = svm

SOURCES += \
    solver.cpp \
    kernel.cpp \
    main.cpp \
    dualproblem.cpp \
    svmproblem.cpp

HEADERS += \
    solver.h \
    kernel.h \
    dualproblem.h \
    svmproblem.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    svm.pri

