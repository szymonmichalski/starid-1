TARGET = starid
TEMPLATE = lib
CONFIG -= qt
CONFIG += c++14 warn_off debug

SOURCES += \
    libstarid.cpp

HEADERS += \
    libstarid.h

include(/home/noah/starid/stars/stars.pri)
include(/home/noah/starid/id/id.pri)

INCLUDEPATH += \
    ../stars \
    ../id \
    ../stars/Eigen \
    /usr/include/python3.5m \
