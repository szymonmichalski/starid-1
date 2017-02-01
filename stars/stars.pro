#TEMPLATE = subdirs
#SUBDIRS = stars rules-based
TEMPLATE = app
CONFIG = console c++14
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

INCLUDEPATH += \
    ../rules-based \
    cereal \
    eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

