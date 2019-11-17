#-------------------------------------------------
#
# Project created by QtCreator 2017-05-25T18:07:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Game2048
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    field.cpp \
    block.cpp

HEADERS  += widget.h \
    field.h \
    block.h
