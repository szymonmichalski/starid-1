DIRBASE = ../base
INCLUDEPATH += $$DIRBASE

HEADERS += \
    $$DIRBASE/catalog.h \
    $$DIRBASE/pointing.h \
    $$DIRBASE/sensor.h \
    $$DIRBASE/training.h \

SOURCES += \
    $$DIRBASE/catalog.cpp \
    $$DIRBASE/pointing.cpp \
    $$DIRBASE/sensor.cpp \
    $$DIRBASE/training.cpp \

DISTFILES += \
    $$DIRBASE/SKYMAP_SKY2000_V5R4.txt
