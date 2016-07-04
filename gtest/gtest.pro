include (../base/base.pri)
include (../pairs/pairs.pri)
include (../knn/knn.pri)
include (../svm/svm.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = gtest

HEADERS += \

SOURCES += \
    base.cpp \
    ptq.cpp \
    main.cpp

INCLUDEPATH += ../../gtest/include
LIBS += ../../gtest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





