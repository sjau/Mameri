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
    src/userprefsform.cpp \
    src/installWizard/installwizard.cpp \
    src/loginForm/loginform.cpp \
    src/mainWindow/mainwindow.cpp

HEADERS  += \
    src/userprefsform.h \
    src/installWizard/installwizard.h \
    src/loginForm/loginform.h \
    src/mainWindow/mainwindow.h

FORMS    += \
    src/userprefsform.ui \
    src/loginForm/loginform.ui \
    src/mainWindow/mainwindow.ui

OTHER_FILES += \
    mameri.sql
