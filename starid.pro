TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    stars \
    convnet \
    pairs \

OTHER_FILES += \
    README.txt \
    LICENSE.txt
