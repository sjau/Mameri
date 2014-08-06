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

SOURCES += main.cpp\
        mainwindow.cpp \
    userprefsform.cpp \
    userloginform.cpp \
    installWizard/installwizard.cpp

HEADERS  += mainwindow.h \
    userprefsform.h \
    userloginform.h \
    installWizard/installwizard.h

FORMS    += mainwindow.ui \
    userprefsform.ui \
    userloginform.ui \
    installWizard/installwizard.ui
