TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    catalog.cpp \
    indexfinder.cpp

HEADERS += \
    catalog.h \
    indexfinder.h \
    util.h
