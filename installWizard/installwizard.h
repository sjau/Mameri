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

    enum { Page_Intro, Page_MySQL, Page_PathOnly, Page_Schema, Page_Admin, Page_Conclusion };

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
    QLabel *mysqlLocationLabel;
    QLineEdit *mysqlLocationLineEdit;
    QPushButton *mysqlLocationPushButton;

private slots:
    void locateMySQLFile();
};




class MySQLPage : public QWizardPage
{
    Q_OBJECT

public:
    MySQLPage(QWidget *parent = 0);
    int nextId() const;
    virtual bool isComplete() const;

private:
    QLabel *mysqlHostLabel;
    QLabel *mysqlPortLabel;
    QLabel *mysqlDatabaseLabel;
    QLabel *mysqlUserLabel;
    QLabel *mysqlPasswordLabel;
    QLabel *mysqlPathLabel;
    QLabel *mysqlDBTestLabel;

    QLineEdit *mysqlHostLineEdit;
    QLineEdit *mysqlPortLineEdit;
    QLineEdit *mysqlDatabaseLineEdit;
    QLineEdit *mysqlUserLineEdit;
    QLineEdit *mysqlPasswordLineEdit;
    QLineEdit *mysqlPathLineEdit;
    QPushButton *mysqlPathPushButton;

private slots:
    void locateMySQLPath();
};




class SchemaPage : public QWizardPage
{
    Q_OBJECT

public:
    SchemaPage(QWidget *parent = 0);
    int nextId() const;

private:
    QLabel *topLabel;
    QRadioButton *addSchemaRadioButton;
    QRadioButton *skipSchemaRadioButton;
    QLineEdit *schemaLineEdit;

private slots:
    void addSchemaSlot();
    void skipSchemaSlot();
};




class AdminPage : public QWizardPage
{
    Q_OBJECT

public:
    AdminPage(QWidget *parent = 0);
    int nextId() const;
    virtual bool isComplete() const;

private:
    QLabel *adminUserLabel;
    QLabel *adminPasswordLabel;
    QLabel *adminPasswordRepeatLabel;
    QLabel *passwordMatchLabel;

    QLineEdit *adminUserLineEdit;
    QLineEdit *adminPasswordLineEdit;
    QLineEdit *adminPasswordRepeatLineEdit;
};




class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);
    int nextId() const;

protected:
    void initializePage();

private:
    QLabel *finishLabel;
};


#endif // INSTALLWIZARD_H
