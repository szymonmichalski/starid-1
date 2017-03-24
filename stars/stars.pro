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
    ../rules-based/star_identifier.cpp \
    ../rules-based/triangle_side.cpp \
    ../rules-based/triangle.cpp

HEADERS += \
    ../rules-based/star_identifier.h \
    ../rules-based/triangle_side.h \
    ../rules-based/triangle.h

INCLUDEPATH += \
    ../rules-based \
    cereal \
    eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo

