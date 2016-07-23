DIRSTARS = ../stars
INCLUDEPATH += $$DIRSTARS

HEADERS += \
    $$DIRSTARS/catalog.h \
    $$DIRSTARS/pointing.h \
    $$DIRSTARS/sensor.h \
    $$DIRSTARS/mnist.h \

SOURCES += \
    $$DIRSTARS/catalog.cpp \
    $$DIRSTARS/pointing.cpp \
    $$DIRSTARS/sensor.cpp \
    $$DIRSTARS/mnist.cpp \

DISTFILES += \
