TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Action/action.cpp \
        Field/game.cpp \
        Gameplay/gameplay.cpp \
        Gameplay/ncurs.cpp \
        main.cpp

HEADERS += \
    Action/action.h \
    Field/game.h \
    Gameplay/drawinterface.h \
    Gameplay/gameplay.h \
    Gameplay/ncurs.h

INCLUDEPATH += /usr/include/ncurses.h
LIBS += -lncurses
