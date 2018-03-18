#-------------------------------------------------
#
# Project created by QtCreator 2018-02-21T14:08:58
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MySQLApplication
TEMPLATE = app

SOURCES += main.cpp\
           mainwindow.cpp\
           sqlconnector.cpp\
           katalogeintrag.cpp\
           person.cpp\
           bearbeiter.cpp\
           autor.cpp\
           add_media.cpp\
           smtp.cpp\
           ausleihender.cpp\
           ausleihliste.cpp\
           ausleihvorgang.cpp\
           katalogliste.cpp

HEADERS  += mainwindow.h\
            katalogeintrag.h\
            sqlconnector.h\
            person.h\
            bearbeiter.h\
            autor.h\
            add_media.h\
            smtp.h\
            ausleihender.h\
            ausleihliste.h\
            ausleihvorgang.h\
            katalogliste.h

FORMS    += mainwindow.ui
