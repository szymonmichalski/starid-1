TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = id

SOURCES += \
    id.cpp \
    triangle_side.cpp \
    triangle.cpp \
    star_identifier.cpp \

HEADERS += \
    triangle_side.h \
    triangle.h \
    star_identifier.h \

SOURCES += \
    ../stars/globals.cpp \
    ../stars/pointing_vectors.cpp \
    ../stars/sky.cpp \
    ../stars/pairs.cpp \
    ../stars/float_int_table.cpp \
    ../stars/star_catalog.cpp \

HEADERS += \
    ../stars/globals.h \
    ../stars/pointing_vectors.h \
    ../stars/sky.h \
    ../stars/pairs.h \
    ../stars/float_int_table.h \
    ../stars/star_catalog.h \
    ../stars/util/stopwatch.h \
    ../stars/util/optionparser.h \

INCLUDEPATH += ../stars

