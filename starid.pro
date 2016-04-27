TEMPLATE = subdirs

SUBDIRS += \
    base \
    unittests \
    ptq \
    knn \
    mlp \
    svm

gtest.depends = base ptq knn mlp knn

OTHER_FILES += \
    README.md \
    LICENSE.txt
