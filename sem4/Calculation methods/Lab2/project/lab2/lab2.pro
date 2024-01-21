TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        abstractgauss.cpp \
        gauss.cpp \
        main.cpp \
        matrix.cpp \
        tasks.cpp \
        timer.cpp

HEADERS += \
    abstractgauss.h \
    gauss.h \
    matrix.h \
    tasks.h \
    timer.h
