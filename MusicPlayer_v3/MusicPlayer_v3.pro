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
    musicmodel.cpp \
    ratingdelegate.cpp \
    albumdialog.cpp \
    artistdialog.cpp \
    trackdialog.cpp

HEADERS  += mainwindow.h \
    item.h \
    musicmodel.h \
    ratingdelegate.h \
    albumdialog.h \
    artistdialog.h \
    trackdialog.h

FORMS    += mainwindow.ui \
    albumdialog.ui \
    artistdialog.ui \
    trackdialog.ui
