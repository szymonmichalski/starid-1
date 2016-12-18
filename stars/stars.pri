DIRSTARS = ../stars
INCLUDEPATH += $$DIRSTARS

HEADERS += \
    $$DIRSTARS/stars.h \
    $$DIRSTARS/sensor.h \
    $$DIRSTARS/mnist.h \
    $$DIRSTARS/float_int_table.h \

SOURCES += \
    $$DIRSTARS/stars.cpp \
    $$DIRSTARS/sensor.cpp \
    $$DIRSTARS/mnist.cpp \
    $$DIRSTARS/float_int_table.cpp \

DISTFILES += \
