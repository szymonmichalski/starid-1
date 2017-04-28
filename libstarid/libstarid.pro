TARGET = starid
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug

SOURCES += \
    libstarid.cpp

HEADERS += \
    libstarid.h

SOURCES += \
    ../stars/globals.cpp \
    ../stars/pointing_vectors.cpp \
    ../stars/sky.cpp \
    ../stars/float_int_table.cpp \
    ../stars/star_catalog.cpp \
    ../stars/pairs.cpp \
    ../id/star_identifier.cpp \
    ../id/triangle.cpp \
    ../id/triangle_side.cpp \

HEADERS += \
    ../stars/globals.h \
    ../stars/pointing_vectors.h \
    ../stars/sky.h \
    ../stars/float_int_table.h \
    ../stars/star_catalog.h \
    ../stars/pairs.h \
    ../id/star_identifier.h \
    ../id/triangle.h \
    ../id/triangle_side.h \

INCLUDEPATH += \
    ../stars \
    ../stars/Eigen \
    /usr/include/python3.5m \
    ../id \
