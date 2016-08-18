TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    stars \
    convnet \
    triangles \

OTHER_FILES += \
    README.txt \
    LICENSE.txt
