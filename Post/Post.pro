#-------------------------------------------------
#
# Project created by QtCreator 2021-04-25T09:06:32
#
#-------------------------------------------------

QT       += core gui

QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Post
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    LinkList.cpp \
    PostMachine.cpp \
    XPost.cpp \
        main.cpp \
        mainwindow.cpp \
    postMath.cpp \
    postParameter.cpp \
    postProcess.cpp \
    postblock.cpp \
    postblockitem.cpp \
    postcommand.cpp \
    settingform.cpp

HEADERS += \
    CLFSmbol.h \
    LinkList.h \
    PostMachine.h \
    XPost.h \
        mainwindow.h \
    postMath.h \
    postParameter.h \
    postProcess.h \
    postblock.h \
    postblockitem.h \
    postcommand.h \
    settingform.h

FORMS += \
        mainwindow.ui \
    blocksform.ui \
    settingform.ui
