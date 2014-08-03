#include "mainwindow.h"
#include <QApplication>
#include <QtSql>
#include <QtWidgets>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mameri");
    db.setUserName("mameri");
    db.setPassword("password");


    db.setConnectOptions();

    if(db.open())   {
        qDebug() << "Opened!";
        MainWindow w;
        w.show();
        db.close();
    }
    else    {
        qDebug() << "Something went Wrong:" << db.lastError().text();
    }

    return a.exec();
}
