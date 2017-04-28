TEMPLATE = app
CONFIG = c++14 warn_off debug
TARGET = id
OTHER_FILES += id.pri

SOURCES += \
    id.cpp \

include(../stars/stars.pri)
include(id.pri)

INCLUDEPATH += ../stars

