#include "userprefsform.h"
#include "ui_userprefsform.h"

userPrefsForm::userPrefsForm(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::userPrefsForm)
{
    ui->setupUi(this);
}

userPrefsForm::~userPrefsForm()
{
    delete ui;
}
