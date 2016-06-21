
DIRSVM = ../svm
INCLUDEPATH += $$DIRSMV

SOURCES += \
    $$DIRSVM/solver.cpp \
    $$DIRSVM/kernel.cpp \
    $$DIRSVM/dualproblem.cpp \
    $$DIRSVM/svmproblem.cpp

HEADERS += \
    $$DIRSVM/solver.h \
    $$DIRSVM/kernel.h \
    $$DIRSVM/dualproblem.h \
    $$DIRSVM/svmproblem.h
