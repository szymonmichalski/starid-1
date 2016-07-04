TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    base \
    pairs \
    svm \
    convnet \
    gtest

OTHER_FILES += \
    README.txt \
    LICENSE.txt
