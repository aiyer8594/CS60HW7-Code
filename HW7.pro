#-------------------------------------------------
#
# Project created by QtCreator 2015-03-09T18:51:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HW7
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    biguint.cpp

HEADERS  += mainwindow.h \
    biguint.h

FORMS    += mainwindow.ui
