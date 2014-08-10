#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QtWidgets>
#include <QtDebug>
#include <QSettings>
#include <QFileInfo>
#include <QFileDialog>

#include "installWizard/installwizard.h"

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
        // Either it's first run --> setup everything
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

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(myHostname);
    db.setPort(myPort);
    db.setDatabaseName(myDbname);
    db.setUserName(myUsername);
    db.setPassword(myPassword);


    db.setConnectOptions();

    if(db.open())   {
        MainWindow w;
        w.show();
        db.close();
    }
    else    {
        qDebug() << "Something went Wrong:" << db.lastError().text();
    }

    return a.exec();
}
