TEMPLATE = subdirs

SUBDIRS += \
    base \
    unittests \
    pairs \
    knn \
    mlp \
    svm

gtest.depends = base pairs patterns neuralnets

OTHER_FILES += \
    README.md \
    LICENSE.txt
