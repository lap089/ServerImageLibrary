#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T21:24:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += UNICODE

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += main.cpp\
    ClientSide.cpp \
    DataEntity.cpp \
    ImageHelper.cpp \
    SocketEx.cpp \
    LoginForm.cpp \
    MainWindow.cpp \
    ImageWindow.cpp \
    DialogUpload.cpp \
    DialogSignup.cpp \
    DialogConnection.cpp

HEADERS  += \
    ClientSide.h \
    Constant.h \
    DataEntity.h \
    ImageHelper.h \
    SocketEx.h \
    LoginForm.h \
    MainWindow.h \
    ImageWindow.h \
    DialogUpload.h \
    DialogSignup.h \
    DialogConnection.h

FORMS    += \
    LoginForm.ui \
    MainWindow.ui \
    ImageWindow.ui \
    DialogUpload.ui \
    DialogSignup.ui \
    DialogConnection.ui


INCLUDEPATH += D:/Program/boost_1_60_0
DEPENDPATH += D:/Program/boost_1_60_0


win32: LIBS += -LD:/Program/boost_1_60_0/stage/lib/ -llibboost_serialization-vc140-mt-gd-1_60

INCLUDEPATH += D:/Program/boost_1_60_0/stage
DEPENDPATH += D:/Program/boost_1_60_0/stage

win32: LIBS += -LD:/Program/boost_1_60_0/stage/lib/ -llibboost_regex-vc140-mt-gd-1_60

INCLUDEPATH += D:/Program/boost_1_60_0/stage
DEPENDPATH += D:/Program/boost_1_60_0/stage

win32: LIBS += -LD:/Program/boost_1_60_0/stage/lib/ -lboost_filesystem-vc140-mt-gd-1_60

INCLUDEPATH += D:/Program/boost_1_60_0/stage
DEPENDPATH += D:/Program/boost_1_60_0/stage
