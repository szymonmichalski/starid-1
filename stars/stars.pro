TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG -= warn_off

TARGET = stars

SOURCES += \
    stars.cpp \
    sky.cpp \
    sensor.cpp \
    ../util/float_int_table.cpp \
    ../data/mnist.cpp \
    ../data/skymap.cpp \

HEADERS += \
    sky.h \
    sensor.h \
    ../util/float_int_table.h \
    ../data/mnist.h \
    ../data/skymap.h \
    ../util/rotations.h \

INCLUDEPATH += \
    ../data \
    ../util \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

