TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    stars \
    pairs \
    convnet \
    gtest

OTHER_FILES += \
    README.txt \
    LICENSE.txt
