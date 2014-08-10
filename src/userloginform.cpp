#include "userloginform.h"
#include "ui_userloginform.h"
#include <QtSql>


userLoginForm::userLoginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userLoginForm)
{
    ui->setupUi(this);
}

userLoginForm::~userLoginForm()
{
    delete ui;
}

void userLoginForm::on_closeButton_clicked()
{

}

void userLoginForm::on_loginButton_clicked()
{
    QString userName,userPasswd;
    userName=ui->userName->text();
    userPasswd=ui->userPasswd->text();

    QSqlDatabase db = QSqlDatabase::database();
    if(!db.open()) {
        qDebug() << "Failed to open DB";
        return;
    }

   QString sql = "SELECT * FROM users WHERE login = :username AND password = :password AND enabled = 1";
   QSqlQuery qry;
   qry.prepare(sql);
   qry.bindValue(":username", userName);
   qry.bindValue(":password", userPasswd);

   if(qry.exec())
   {
       qDebug() << "Run query... maybe...";
   }

   qDebug() << "Didn't run query";

}
