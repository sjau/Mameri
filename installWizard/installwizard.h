#ifndef INSTALLWIZARD_H
#define INSTALLWIZARD_H

#include <QWizard>

class QCheckBox;
class QLabel;
class QLineEdit;
class QRadioButton;

namespace Ui {
class installWizard;
}

class installWizard : public QWizard
{
    Q_OBJECT

public:

    enum { Page_Intro, Page_MySQL, Page_PathOnly, Page_Conclusion };

    explicit installWizard(QWidget *parent = 0);
    ~installWizard();

private:
    Ui::installWizard *ui;
};



class IntroPage : public QWizardPage
{
    Q_OBJECT

public:
    IntroPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *topLabel;
    QRadioButton *pathRadioButton;
    QRadioButton *fullRadioButton;
};



class PathOnlyPage : public QWizardPage
{
    Q_OBJECT

public:
    PathOnlyPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *pathLabel;
    QLineEdit *pathLineEdit;
    QPushButton *pathPushButton;

private slots:
    void selectMySQLFile();
};



class MySQLPage : public QWizardPage
{
    Q_OBJECT

public:
    MySQLPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *nameLabel;
    QLabel *upgradeKeyLabel;
    QLineEdit *nameLineEdit;
    QLineEdit *upgradeKeyLineEdit;
};



class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    void initializePage();
    int nextId() const;

private:
    QLabel *bottomLabel;
    QCheckBox *agreeCheckBox;
};


#endif // INSTALLWIZARD_H
