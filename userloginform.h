#ifndef USERLOGINFORM_H
#define USERLOGINFORM_H

#include <QDialog>

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

private:
    Ui::userLoginForm *ui;
};

#endif // USERLOGINFORM_H
