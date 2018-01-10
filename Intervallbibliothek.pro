#-------------------------------------------------
#
# Project created by QtCreator 2017-11-09T18:40:36
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = Intervallbibliothek
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES  += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        sources/main.cpp \
        sources/mainwindow.cpp \
        sources/smtp.cpp \
        sources/katalogeintrag.cpp \
        sources/autor.cpp \
        sources/sqlconnector.cpp

HEADERS += \
        headers/mainwindow.h \
        headers/cppconn/connection.h \
        headers/smtp.h \
        headers/katalogeintrag.h \
        headers/autor.h \
        headers/sqlconnector.h

FORMS   += \
        mainwindow.ui \
        mainwindow.ui

INCLUDEPATH += \
        -I/usr/include \
        -I/usr/local/include \
        -I/usr/local/include/cppconn

LIBS += \
        -lGL

LIBS += \
        -L/usr/local/lib \
        -L/usr/lib/ \
        -lmysqlcppconn
