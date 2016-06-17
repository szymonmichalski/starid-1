TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = gtest

DIR1 = ../base
DIR2 = ../ptq
DIR3 = ../knn
DIR4 = ../svm
INCLUDEPATH += $$DIR1
INCLUDEPATH += $$DIR2
INCLUDEPATH += $$DIR3
INCLUDEPATH += $$DIR4

HEADERS += \
    $$DIR1/catalog.h \
    $$DIR1/pointing.h \
    $$DIR1/sensor.h \
    $$DIR1/training.h \
    $$DIR2/pairs.h \
    $$DIR2/triplets.h \
    $$DIR3/knntrain.h \
    $$DIR4/svmtrain.h

SOURCES += \
    $$DIR1/catalog.cpp \
    $$DIR1/pointing.cpp \
    $$DIR1/sensor.cpp \
    $$DIR1/training.cpp \
    $$DIR2/pairs.cpp \
    $$DIR2/triplets.cpp \
    $$DIR3/knntrain.cpp \
    $$DIR4/svmtrain.cpp \
    base_pointing.cpp \
    main.cpp \
    knn_endtoend.cpp \
    ptq_endtoend.cpp \
    base_endtoend.cpp \
    knn_simple.cpp

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





