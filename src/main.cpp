#include <QApplication>
#include <QtSql>
#include <QtWidgets>
#include <QtDebug>
#include <QSettings>
#include <QFileInfo>
#include <QFileDialog>

#include "mainWindow/mainwindow.h"
#include "installWizard/installwizard.h"
#include "loginForm/loginform.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load path to the mysql settings file
    QSettings myPath("Mameri", "mameri");
    myPath.beginGroup("MySQLPath");
    QString myLocation = myPath.value("location").toString();
    myPath.endGroup();

    QFileInfo myIni(myLocation);
    if(!myIni.isFile())
    {
        // Run install wizard
        installWizard wizard;
        wizard.exec();
    }
    // Load MySQL Settings
    QSettings myDBSettings(myLocation, QSettings::IniFormat);
    myDBSettings.beginGroup("MySQL");
    QString myHostname  = myDBSettings.value("hostname").toString();
    int myPort          = myDBSettings.value("port").toInt();
    QString myDbname    = myDBSettings.value("dbname").toString();
    QString myUsername  = myDBSettings.value("username").toString();
    QString myPassword  = myDBSettings.value("password").toString();
    myDBSettings.endGroup();

    // Connect to DB
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(myHostname);
    db.setPort(myPort);
    db.setDatabaseName(myDbname);
    db.setUserName(myUsername);
    db.setPassword(myPassword);

    db.setConnectOptions();

    if(db.open())   {
        // User Login
        bool isValid = false;
        qApp->setProperty("isValid", isValid);

        loginForm loginFormObj;
        loginFormObj.setModal(true);
        int cancelLogin = loginFormObj.exec();
        // Kill process if cancel was used
        if(cancelLogin == 0) return 0;

        qDebug() << "Valid User? " << qApp->property("isValid");
        qDebug() << "User ID? " << qApp->property("userId");
        // Start main application window
    } else
    {
        qDebug() << "Couldn't connect to DB:" << db.lastError().text();
        qApp->quit();
    }
    mainWindow w;
    w.show();

    return a.exec();
}
