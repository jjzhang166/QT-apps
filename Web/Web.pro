#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T02:40:25
#
#-------------------------------------------------

QT       += core gui webkit webkitwidgets
//QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Web
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webplugin.cpp \
    widget.cpp

HEADERS  += mainwindow.h \
    webplugin.h \
    widget.h

FORMS    += mainwindow.ui

RESOURCES += \
    Report/report.qrc
