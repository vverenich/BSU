TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractgauss.cpp \
        gauss.cpp \
        gausscolumnselection.cpp \
        gaussjordan.cpp \
        main.cpp \
        matrix.cpp \
        printer.cpp \
        relaxation.cpp \
        tasks.cpp \
        timer.cpp

HEADERS += \
    abstractgauss.h \
    gauss.h \
    gausscolumnselection.h \
    gaussjordan.h \
    matrix.h \
    printer.h \
    relaxation.h \
    tasks.h \
    timer.h
