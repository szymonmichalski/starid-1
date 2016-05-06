TEMPLATE = subdirs

CONFIG += c++14
CONFIG += warn_off

SUBDIRS += \
    base \
    unittests \
    ptq \
    knn \
    mlp \
    svm

unittests.depends = base ptq knn mlp knn

OTHER_FILES += \
    README.md \
    LICENSE.txt
