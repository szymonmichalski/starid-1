TEMPLATE = subdirs

SUBDIRS += \
    base \
    gtest

gtest.depends = base

OTHER_FILES += \
    README.md \
    LICENSE.txt
