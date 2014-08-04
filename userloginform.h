#ifndef USERLOGINFORM_H
#define USERLOGINFORM_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class userLoginForm;
}

class userLoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit userLoginForm(QWidget *parent = 0);
    ~userLoginForm();

private slots:
    void on_closeButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::userLoginForm *ui;
};

#endif // USERLOGINFORM_H
