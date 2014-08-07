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

    enum { Page_Intro, Page_MySQL, Page_PathOnly, Page_Schema, Page_Conclusion };

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

private:
    QLabel *mysqlHostLabel;
    QLabel *mysqlPortLabel;
    QLabel *mysqlDatabaseLabel;
    QLabel *mysqlUserLabel;
    QLabel *mysqlPasswordLabel;
    QLabel *mysqlPathLabel;

    QLineEdit *mysqlHostLineEdit;
    QLineEdit *mysqlPortLineEdit;
    QLineEdit *mysqlDatabaseLineEdit;
    QLineEdit *mysqlUserLineEdit;
    QLineEdit *mysqlPasswordLineEdit;
    QLineEdit *mysqlPathLineEdit;
    QPushButton *mysqlPathPushButton;
    QPushButton *mysqlTestPushButton;

private slots:
    void locateMySQLPath();
    void testMySQLConnection();
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
};




class ConclusionPage : public QWizardPage
{
    Q_OBJECT

public:
    ConclusionPage(QWidget *parent = 0);

    int nextId() const;

private:
    QLabel *finishLabel;
};


#endif // INSTALLWIZARD_H
