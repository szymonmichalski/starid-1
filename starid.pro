TEMPLATE = subdirs

SUBDIRS += \
    base \
    gtest \
    pairs \
    patterns \
    neuralnets

gtest.depends = base

OTHER_FILES += \
    README.md \
    LICENSE.txt
