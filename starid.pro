TEMPLATE = subdirs

SUBDIRS += \
    base \
    gtest \
    pairs \
    patterns \
    neuralnets

gtest.depends = base pairs patterns neuralnets

OTHER_FILES += \
    README.md \
    LICENSE.txt
