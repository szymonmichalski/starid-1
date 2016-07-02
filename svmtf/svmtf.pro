include (../base/base.pri)
include (../svm/svm.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = svmtf

SOURCES += \
    main.cpp

HEADERS += \


INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    tftest.py \
    mnist2.py \
    fully_connected_feed.py \
    mnist1.py \
    mnist3.py
