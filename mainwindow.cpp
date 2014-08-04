#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "userprefsform.h"
#include "userloginform.h"
#include <QtSql>

MainWindow::MainWindow(QSqlDatabase db, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    userLoginForm loginForm;
    loginForm.setModal(true);
    loginForm.exec(db);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBenutzereinstellungen_triggered()
{
    userPrefsForm* userprefsform = new userPrefsForm(this);
    userprefsform->show();
}
