TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    base \
    unittests \
    ptq \
    knn \
    svm \
    ann

unittests.depends = base ptq knn svm ann

OTHER_FILES += \
    README.md \
    LICENSE.txt
