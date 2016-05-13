TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = unittests

SOURCES += \
    base_pointing.cpp \
    main.cpp \
    knn_l2.cpp \
    knn_endtoend.cpp \
    ptq_endtoend.cpp \
    base_endtoend.cpp

HEADERS += \

INCLUDEPATH += ../base
LIBS += ../base/pointing.o
LIBS += ../base/catalog.o
LIBS += ../base/sensor.o

INCLUDEPATH += ../ptq
LIBS += ../ptq/pairs.o
LIBS += ../ptq/triplets.o

INCLUDEPATH += ../knn
LIBS += ../knn/l2.o

INCLUDEPATH += ../../googletest/include
LIBS += ../../googletest/libgtest.a
LIBS += -pthread

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so





