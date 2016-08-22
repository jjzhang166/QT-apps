#-------------------------------------------------
#
# Project created by QtCreator 2016-08-18T19:56:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MusicPlayer_v3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    item.cpp \
    musicmodel_v3.cpp \
    musicmodel.cpp \
    ratingdelegate.cpp

HEADERS  += mainwindow.h \
    item.h \
    musicmodel_v3.h \
    musicmodel.h \
    ratingdelegate.h

FORMS    += mainwindow.ui
