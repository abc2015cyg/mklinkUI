#-------------------------------------------------
#
# Project created by QtCreator 2015-03-14T19:31:48
#
#-------------------------------------------------

QT       += core gui\
            sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mklinkGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myfiledialog.cpp \
    mylineedit.cpp

HEADERS  += mainwindow.h \
    myfiledialog.h \
    mylineedit.h

FORMS    += mainwindow.ui

CONFIG += c++11
