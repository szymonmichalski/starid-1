#TEMPLATE = subdirs
#SUBDIRS = stars rb
TEMPLATE = app
CONFIG = c++14 warn_off
TARGET = rb

SOURCES += \
    rb.cpp \
    triangle_side.cpp \
    triangle.cpp \
    star_identifier.cpp

HEADERS += \
    triangle_side.h \
    triangle.h \
    star_identifier.h

SOURCES += \
    ../stars/globals.cpp \
    ../stars/image.cpp \
    ../stars/sky.cpp \
    ../stars/pairs.cpp \
    ../stars/float_int_table.cpp \
    ../stars/skymap.cpp \
    ../stars/mnist.cpp

HEADERS += \
    ../stars/globals.h \
    ../stars/image.h \
    ../stars/sky.h \
    ../stars/pairs.h \
    ../stars/float_int_table.h \
    ../stars/skymap.h \
    ../stars/mnist.h \
    ../stars/util/stopwatch.h \
    ../stars/util/optionparser.h

INCLUDEPATH += \
    ../stars \
    ../stars/cereal \
    ../stars/eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo


