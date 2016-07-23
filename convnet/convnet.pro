include (../stars/stars.pri)

TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++14
CONFIG += warn_off

TARGET = convnet

SOURCES += \
    convnet_main.cpp \
    knntrain.cpp \
    svmmodel.cpp \
    svmtrain.cpp \

HEADERS += \
    knntrain.h \
    svmmodel.h \
    svmtrain.h

INCLUDEPATH += ../../armadillo
LIBS += ../../armadillo/libarmadillo.so

DISTFILES += \
    convnet.py \
    convnet_train.py
