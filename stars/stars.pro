#TEMPLATE = subdirs
#SUBDIRS = stars rb
TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = stars

SOURCES += \
    stars.cpp \
    globals.cpp \
    sky.cpp \
    image.cpp \
    float_int_table.cpp \
    mnist.cpp \
    skymap.cpp \
    pairs.cpp

HEADERS += \
    globals.h \
    sky.h \
    image.h \
    float_int_table.h \
    mnist.h \
    skymap.h \
    util/stopwatch.h \
    util/optionparser.h \
    pairs.h

SOURCES += \
    ../rb/star_identifier.cpp \
    ../rb/triangle_side.cpp \
    ../rb/triangle.cpp

HEADERS += \
    ../rb/star_identifier.h \
    ../rb/triangle_side.h \
    ../rb/triangle.h

INCLUDEPATH += \
    ../rb \
    cereal \
    eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

