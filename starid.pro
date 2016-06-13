TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    base \
    unittests \
    ptq \
    knn \
    svm \
    tf

unittests.depends = base ptq knn svm

OTHER_FILES += \
    README.md \
    LICENSE.txt
