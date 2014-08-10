#-------------------------------------------------
#
# Project created by QtCreator 2014-07-30T15:50:28
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Mameri
TEMPLATE = app

SOURCES +=\
    src/main.cpp \
    src/mainwindow.cpp \
    src/userprefsform.cpp \
    src/userloginform.cpp \
    src/installWizard/installwizard.cpp

HEADERS  += \
    src/mainwindow.h \
    src/userprefsform.h \
    src/userloginform.h \
    src/installWizard/installwizard.h

FORMS    += \
    src/mainwindow.ui \
    src/userprefsform.ui \
    src/userloginform.ui

OTHER_FILES += \
    mameri.sql
