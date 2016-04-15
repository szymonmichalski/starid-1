TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    base.cpp \
    catalog.cpp \
    indexfinder.cpp \
    sensor.cpp \
    starpairs.cpp

HEADERS += \
    base.h \
    catalog.h \
    indexfinder.h \
    sensor.h \
    starpairs.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../armadillo-6.600.4/release/ -larmadillo
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../armadillo-6.600.4/debug/ -larmadillo
else:unix: LIBS += -L$$PWD/../../armadillo-6.600.4/ -larmadillo

INCLUDEPATH += $$PWD/../../armadillo-6.600.4
DEPENDPATH += $$PWD/../../armadillo-6.600.4
