#-------------------------------------------------
#
# Project created by QtCreator 2015-11-19T10:20:23
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RedSocial
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    LoginWindow.cpp \
    RegisterWindow.cpp \
    APIHandler.cpp \
    StatusWindow.cpp \
    EditWindow.cpp \
    UserWindow.cpp

HEADERS  += mainwindow.h \
    LoginWindow.h \
    RegisterWindow.h \ 
    APIHandler.h \
    StatusWindow.h \
    EditWindow.h \
    UserWindow.h

FORMS    += mainwindow.ui \
    LoginWindow.ui \
    RegisterWindow.ui \
    StatusWindow.ui \
    EditWindow.ui \
    UserWindow.ui
