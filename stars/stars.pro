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
    ../rules-based/pairs_over_whole_sky.cpp \
    ../rules-based/triangles.cpp \

HEADERS += \
    sky.h \
    sensor.h \
    ../util/float_int_table.h \
    ../data/mnist.h \
    ../data/skymap.h \
    ../util/optionparser.h \
    ../util/stopwatch.h \
    ../rules-based/pairs_over_whole_sky.h \
    ../rules-based/triangles.h \

INCLUDEPATH += \
    ../rules-based \
    ../data \
    ../util \
    ../util/cereal \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

