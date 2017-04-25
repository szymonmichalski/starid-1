TARGET = starsop
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug
QMAKE_CXXFLAGS = -D_GLIBCXX_USE_CXX11_ABI=0

SOURCES += \
    libstarsop.cpp

HEADERS += \
    libstarsop.h

INCLUDEPATH += /home/noah/tf/lib/python3.5/site-packages/tensorflow/include

SOURCES += \
    ../stars/globals.cpp \
    ../stars/pointing_vectors.cpp \
    ../stars/sky.cpp \
    ../stars/float_int_table.cpp \
    ../stars/star_catalog.cpp \

HEADERS += \
    ../stars/globals.h \
    ../stars/pointing_vectors.h \
    ../stars/sky.h \
    ../stars/float_int_table.h \
    ../stars/star_catalog.h \

INCLUDEPATH += ../stars
