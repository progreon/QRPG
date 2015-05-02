#-------------------------------------------------
#
# Project created by QtCreator 2015-05-02T17:10:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRPGGame
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    screen.cpp \
    game.cpp \
    maps/mapfactory.cpp \
    graphicsitem.cpp \
    scene.cpp \
    maps/map.cpp \
    battles/battlescene.cpp \
    tiles/tile.cpp

HEADERS  += mainwindow.h \
    screen.h \
    game.h \
    maps/mapfactory.h \
    graphicsitem.h \
    scene.h \
    maps/map.h \
    battles/battlescene.h \
    tiles/tile.h

FORMS    += mainwindow.ui
