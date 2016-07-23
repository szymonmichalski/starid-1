TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    stars \
    pairs \
    svm \
    convnet \
    gtest

OTHER_FILES += \
    README.txt \
    LICENSE.txt
