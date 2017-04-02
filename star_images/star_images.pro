TARGET = star_images
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug
QMAKE_CXXFLAGS = -D_GLIBCXX_USE_CXX11_ABI=0

SOURCES += \
    star_images.cpp

HEADERS += \
    star_images.h

INCLUDEPATH += /home/noah/tf/lib/python3.5/site-packages/tensorflow/include

