TEMPLATE = app
CONFIG = c++14 warn_on debug
TARGET = stars

SOURCES += \
    stars.cpp \
    globals.cpp \
    pairs.cpp \
    star_catalog.cpp \
    sky.cpp \
    float_int_table.cpp \
    images.cpp

HEADERS += \
    globals.h \
    pairs.h \
    star_catalog.h \
    sky.h \
    float_int_table.h \
    util/stopwatch.h \
    util/optionparser.h \
    images.h

