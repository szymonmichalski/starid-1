TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = rules-based

SOURCES += \
    rules-based.cpp \
    triangles_in_star_image.cpp \
    pairs_over_whole_sky.cpp \
    ../stars/sensor.cpp \
    ../stars/sky.cpp \
    ../util/float_int_table.cpp \
    ../data/skymap.cpp \

HEADERS += \
    triangles_in_star_image.h \
    pairs_over_whole_sky.h \
    ../stars/sensor.h \
    ../stars/sky.h \
    ../util/float_int_table.h \
    ../data/skymap.h \

INCLUDEPATH += \
    ../stars \
    ../util \
    ../data \

INCLUDEPATH += /usr/include/armadillo_bits
LIBS += -L"/usr/lib" -larmadillo
