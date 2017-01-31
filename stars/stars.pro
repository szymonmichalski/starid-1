#TEMPLATE = subdirs
#SUBDIRS += \
#    stars \
#    rules-based \
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
    ../util/float_int_table.cpp \
    ../data/mnist.cpp \
    ../data/skymap.cpp \
    ../rules-based/pairs_over_whole_sky.cpp \
    ../rules-based/triangles.cpp \
    image.cpp \
    globals.cpp

HEADERS += \
    sky.h \
    ../util/float_int_table.h \
    ../data/mnist.h \
    ../data/skymap.h \
    ../util/optionparser.h \
    ../util/stopwatch.h \
    ../rules-based/pairs_over_whole_sky.h \
    ../rules-based/triangles.h \
    image.h \
    globals.h \

INCLUDEPATH += \
    ../rules-based \
    ../data \
    ../util \
    ../util/cereal \
    ../util/eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

