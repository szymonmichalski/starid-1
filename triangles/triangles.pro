include (../stars/stars.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = triangles

SOURCES += \
    triangles_main.cpp \
    pairs_over_whole_sky.cpp \
    triangles_in_star_image.cpp

HEADERS += \
    pairs_over_whole_sky.h \
    triangles_in_star_image.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \

