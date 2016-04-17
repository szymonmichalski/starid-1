TEMPLATE = subdirs

SUBDIRS += \
    base \
    gtest \
    pairs

gtest.depends = base

OTHER_FILES += \
    README.md \
    LICENSE.txt
