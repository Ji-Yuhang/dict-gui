#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T17:00:43
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dict-gui
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    exportwidget.cpp \
    json.cpp

HEADERS  += mainwindow.hxx \
    exportwidget.hxx \
    json.h

FORMS    += mainwindow.ui \
    exportwidget.ui
unix {
#INCLUDEPATH += /home/jiyuhang/program/jyhsdk/cpp/include
#LIBS += -L/home/jiyuhang/program/jyhsdk/cpp/lib
#LIBS += -ljyh
}
