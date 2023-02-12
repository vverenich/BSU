TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        alternativeinterface.cpp \
        ddsdistributedroboticsystem.cpp \
        decisionsupportsysteminterface.cpp \
        distributedroboticsystem.cpp \
        main.cpp \
        mainmenu.cpp \
        typeofrobot.cpp

HEADERS += \
    alternativeinterface.h \
    ddsdistributedroboticsystem.h \
    decisionsupportsysteminterface.h \
    distributedroboticsystem.h \
    mainmenu.h \
    typeofrobot.h
