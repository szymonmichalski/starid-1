TEMPLATE = subdirs

SUBDIRS += \
    base \
    unittests \
    pairs \
    knn \
    mlp \
    svn

gtest.depends = base pairs patterns neuralnets

OTHER_FILES += \
    README.md \
    LICENSE.txt
