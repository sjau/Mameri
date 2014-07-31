#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include "userprefsform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionBenutzereinstellungen_triggered()
{
    userPrefsForm userprefsform;
//    userprefsform.setModal(true);
    userprefsform.show();
}
