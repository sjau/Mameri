#include "userloginform.h"
#include "ui_userloginform.h"

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
