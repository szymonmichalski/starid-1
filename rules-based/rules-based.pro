TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = rb

SOURCES += \
    pairs_over_whole_sky.cpp \
    ../stars/image.cpp \
    ../stars/sky.cpp \
    ../util/float_int_table.cpp \
    ../data/skymap.cpp \
    triangles.cpp \
    rb.cpp \
    ../data/mnist.cpp \
    ../stars/globals.cpp \

HEADERS += \
    pairs_over_whole_sky.h \
    ../stars/image.h \
    ../stars/sky.h \
    ../util/float_int_table.h \
    ../data/skymap.h \
    ../util/optionparser.h \
    triangles.h \
    ../util/stopwatch.h \
    ../data/mnist.h \
    ../stars/globals.h \

INCLUDEPATH += \
    ../stars \
    ../util \
    ../data \
    ../util/cereal \
    ../util/eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo
