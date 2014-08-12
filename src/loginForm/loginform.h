#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class loginForm;
}

class loginForm : public QDialog
{
    Q_OBJECT

public:
    explicit loginForm(QWidget *parent = 0);
    ~loginForm();

private slots:
    void on_cancelButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::loginForm *ui;
};

#endif // LOGINFORM_H
