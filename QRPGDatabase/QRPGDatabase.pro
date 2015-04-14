#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T16:38:33
#
#-------------------------------------------------

QT       -= gui

TARGET = QRPGDatabase
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qrpgdatabase.cpp \
    impl/qrpgdummydao.cpp \
    impl/qrpgfiledao.cpp \
    model/qrpgproject.cpp

HEADERS += qrpgdatabase.h \
    impl/qrpgdummydao.h \
    impl/qrpgfiledao.h \
    model/qrpgproject.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}