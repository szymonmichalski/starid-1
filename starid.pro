TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    base \
    pairs \
    knn \
    svm \
    gtest \
    tf

OTHER_FILES += \
    README.txt \
    LICENSE.txt
