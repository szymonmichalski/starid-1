TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = rb

SOURCES += \
    rb.cpp \
    triangles.cpp \
    pairs_over_whole_sky.cpp \
    ../stars/globals.cpp \
    ../stars/image.cpp \
    ../stars/sky.cpp \
    ../stars/float_int_table.cpp \
    ../stars/skymap.cpp \
    ../stars/mnist.cpp \

HEADERS += \
    triangles.h \
    pairs_over_whole_sky.h \
    ../stars/globals.h \
    ../stars/image.h \
    ../stars/sky.h \
    ../stars/float_int_table.h \
    ../stars/skymap.h \
    ../stars/stopwatch.h \
    ../stars/mnist.h \
    ../stars/optionparser.h \

INCLUDEPATH += \
    ../stars \
    ../stars/cereal \
    ../stars/eigen \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo


