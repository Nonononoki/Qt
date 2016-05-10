#-------------------------------------------------
#
# Project created by QtCreator 2016-03-04T23:07:51
#
#-------------------------------------------------

QT       += core gui opengl

LIBS    += -lOpengl32

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = opengl4
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    oglwidget.cpp \
    kugel.cpp \
    vector.cpp

HEADERS  += mainwindow.h \
    oglwidget.h \
    kugel.h \
    vector.h

FORMS    += mainwindow.ui
