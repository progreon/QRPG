#-------------------------------------------------
#
# Project created by QtCreator 2015-04-13T17:26:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QRPGMaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

unix:!macx:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-QRPGDatabase-Desktop_Qt_5_4_1_GCC_64bit-Release/ -lQRPGDatabase
else:unix:!macx:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-QRPGDatabase-Desktop_Qt_5_4_1_GCC_64bit-Debug/ -lQRPGDatabase

INCLUDEPATH += $$PWD/../QRPGDatabase
DEPENDPATH += $$PWD/../QRPGDatabase

unix:!macx:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../build-QRPGDatabase-Desktop_Qt_5_4_1_GCC_64bit-Release/libQRPGDatabase.a
else:unix:!macx:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../build-QRPGDatabase-Desktop_Qt_5_4_1_GCC_64bit-Debug/libQRPGDatabase.a
