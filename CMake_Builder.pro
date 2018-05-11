#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T14:56:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CMake_Builder
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cmake_build.cpp \
    project_guide.cpp

HEADERS  += mainwindow.h \
    cmake_build.h \
    project_guide.h \
    project_config.h

FORMS    += mainwindow.ui \
    project_guide.ui
