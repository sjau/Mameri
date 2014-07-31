#ifndef USERPREFSFORM_H
#define USERPREFSFORM_H

#include <QTabWidget>

namespace Ui {
class userPrefsForm;
}

class userPrefsForm : public QTabWidget
{
    Q_OBJECT

public:
    explicit userPrefsForm(QWidget *parent = 0);
    ~userPrefsForm();

private:
    Ui::userPrefsForm *ui;
};

#endif // USERPREFSFORM_H
