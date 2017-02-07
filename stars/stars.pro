#TEMPLATE = subdirs
#SUBDIRS = stars rules-based
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
    ../rules-based/pairs_over_whole_sky.cpp \
    ../rules-based/triangles.cpp \
    ../rules-based/triangle_side.cpp \

HEADERS += \
    globals.h \
    sky.h \
    image.h \
    float_int_table.h \
    mnist.h \
    skymap.h \
    stopwatch.h \
    optionparser.h \
    ../rules-based/pairs_over_whole_sky.h \
    ../rules-based/triangles.h \
    ../rules-based/triangle_side.h \

INCLUDEPATH += \
    ../rules-based \
    cereal \
    eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

