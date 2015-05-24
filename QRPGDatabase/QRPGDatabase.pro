#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T16:38:33
#
#-------------------------------------------------

QT       += gui

TARGET = QRPGDatabase
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qrpgdatabase.cpp \
    impl/qrpgfiledao.cpp \
    model/qrpgproject.cpp \
    model/qrpgmap.cpp \
    model/qrpgtile.cpp \
    impl/loaders/maploader.cpp \
    model/qrpgsprite.cpp

HEADERS += qrpgdatabase.h \
    impl/qrpgfiledao.h \
    model/qrpgproject.h \
    model/qrpgmap.h \
    model/qrpgtile.h \
    impl/loaders/maploader.h \
    model/qrpgsprite.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

RESOURCES += \
    files.qrc
