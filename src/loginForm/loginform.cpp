#include "loginform.h"
#include "ui_loginform.h"
#include <QtSql>


loginForm::loginForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);
}

loginForm::~loginForm()
{
    delete ui;
}

void loginForm::on_cancelButton_clicked()
{
    this->reject();
}

void loginForm::on_loginButton_clicked()
{
    QString userName,userPasswd;
    userName=ui->userName->text();
    userPasswd=ui->userPasswd->text();

    QSqlDatabase db = QSqlDatabase::database();
    if(!db.isOpen()) {
        qDebug() << "DB is not open!";
        return;
    }

    // Get salt for user
    QString sql = "SELECT salt FROM users WHERE login = :username AND enabled = 1";
    QSqlQuery qry;
    qry.prepare(sql);
    qry.bindValue(":username", userName);
    qry.exec();
    QString userSalt = qry.value(0).toString();

    // Make hashed password
    userPasswd.append(userSalt);
    QByteArray hashed = QCryptographicHash::hash(userPasswd.toUtf8(), QCryptographicHash::Sha3_256);
    QString hashedPasswd(hashed.toHex().constData());

    // Get user with hashed password
    sql = "SELECT id FROM users WHERE login = :username AND password = :password AND enabled = 1";
    qry.prepare(sql);
    qry.bindValue(":username", userName);
    qry.bindValue(":password", hashedPasswd);

    if(qry.exec())
    {
        qry.first();
        int number = qry.size();
        if(number == 1)
        {
            qDebug() << "User logged in.";
            bool isValid = true;
            int userId = qry.value(0).toInt();
            qDebug() << qry.lastError();

            qApp->setProperty("isValid", isValid);
            qApp->setProperty("userId", userId);
            this->accept();
        } else
        {
            qDebug() << "Wrong login info.";
            ui->errorLabel->setText(tr("Error, couldn't login. Try again."));
        }
    } else
    {
        qDebug() << "Query didn't run...";
    }
}
