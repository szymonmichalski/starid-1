TEMPLATE = subdirs

SUBDIRS += \
    base \
    unittests \
    pairs \
    patterns \
    neuralnets

gtest.depends = base pairs patterns neuralnets

OTHER_FILES += \
    README.md \
    LICENSE.txt
