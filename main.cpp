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
    QSettings setting("Mameri", "mameri");
    setting.beginGroup("MySQLPath");
    QString mysqlLocation = setting.value("location").toString();
    setting.endGroup();

    QFileInfo mysqlIni(mysqlLocation);
    if(!mysqlIni.isFile())
    {
        // Run install wizard
        installWizard wizard;
        wizard.exec();
        // Either it's first run --> setup everything

        // Or it's just a new computer --> set path to mysql settings file
        QString mysqlFileName;
        do
        {
            qDebug() << "No mysql settings file selected";
            mysqlFileName = QFileDialog::getOpenFileName(0, "Select File", "", "MySQL Settings (Mameri.mysql.ini)");
        } while(QString(mysqlFileName).isNull());
        // Store the path to the mysql settings file
        QFileInfo mysqlFilePath(mysqlFileName);
        QSettings setting("Mameri", "mameri");
        setting.beginGroup("MySQLPath");
        setting.setValue("location", mysqlFilePath.absoluteFilePath());
        setting.endGroup();
    }
    // Load MySQL Settings
    QSettings mysqlSettings(mysqlLocation, QSettings::IniFormat);
    QString myHostname  = mysqlSettings.value("hostname").toString();
    QString myDbname    = mysqlSettings.value("dbname").toString();
    QString myUsername  = mysqlSettings.value("username").toString();
    QString myPassword  = mysqlSettings.value("password").toString();


    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(myHostname);
    db.setDatabaseName(myDbname);
    db.setUserName(myUsername);
    db.setPassword(myPassword);


    db.setConnectOptions();

    if(db.open())   {
        qDebug() << "Opened!";

        // Check if Tables are already setup and if there's an administrative user
        // Will be put into first run later...
        QString sql = "SELECT * FROM users WHERE role = 1";
        QSqlQuery qry;
        qry.prepare(sql);
        if(qry.exec())
        {
            if(qry.size() < 1)
            {
                qDebug() << "no admin user yet";
                // No admin user found, run the first run window
                //firstRunWindow firstRun;
                //firstRun.show();
            }
        }


        MainWindow w;
        w.show();
        db.close();
    }
    else    {
        qDebug() << "Something went Wrong:" << db.lastError().text();
    }

    return a.exec();
}

