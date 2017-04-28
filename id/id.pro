TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = id
OTHER_FILES += id.pri

SOURCES += \
    id.cpp \

include(/home/noah/starid/stars/stars.pri)
include(/home/noah/starid/id/id.pri)

INCLUDEPATH += ../stars

