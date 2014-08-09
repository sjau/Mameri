#include "installwizard.h"
#include "ui_installwizard.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QObject>
#include <QtSql>
#include <QDialog>
#include <QSettings>
#include <QFile>
#include <QTextStream>
#include <QUuid>
#include <QCryptographicHash>

#include <QByteArray>


installWizard::installWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::installWizard)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_MySQL, new MySQLPage);
    setPage(Page_PathOnly, new PathOnlyPage);
    setPage(Page_Schema, new SchemaPage);
    setPage(Page_Admin, new AdminPage);
    setPage(Page_Conclusion, new ConclusionPage);

    setStartId(Page_Intro);

    setWindowTitle(tr("Wizard Wizard"));

    ui->setupUi(this);
}

installWizard::~installWizard()
{
    delete ui;
}

IntroPage::IntroPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Introduction"));

    topLabel = new QLabel(tr("This wizard will help you to setup Mameri.<br>"
                             "- Use 'Locate MySql Config File' if Mameri is already setup on your network.<br>"
                             "- Use 'Install Mameri Server' if there's isn't anything setup yet.<br>"
                             "&nbsp;&nbsp;or if you need to recreate the MySQL Config File."));
    topLabel->setWordWrap(true);

    pathRadioButton = new QRadioButton(tr("Locate MySQL Config File"));
    fullRadioButton = new QRadioButton(tr("Install Mameri Server"));
    pathRadioButton->setChecked(true);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(pathRadioButton);
    layout->addWidget(fullRadioButton);
    setLayout(layout);
}

int IntroPage::nextId() const
{
    if (pathRadioButton->isChecked()) {
        return installWizard::Page_PathOnly;
    } else {
        return installWizard::Page_MySQL;
    }
}




PathOnlyPage::PathOnlyPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Locate MySQL Config File"));
    setSubTitle(tr("Choose path to your MySQL Config File. Ask your admin for help."));

    mysqlLocationLabel = new QLabel(tr("MySQL Config File Location:"));
    mysqlLocationLineEdit = new QLineEdit;
    mysqlLocationLabel->setBuddy(mysqlLocationLineEdit);

    mysqlLocationPushButton = new QPushButton(tr("Locate MySQL Config File"));;
    connect(mysqlLocationPushButton, SIGNAL(clicked()), this, SLOT(locateMySQLFile()));

    registerField("mysqlLocation*", mysqlLocationLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mysqlLocationLabel, 0, 0);
    layout->addWidget(mysqlLocationLineEdit, 0, 1);
    layout->addWidget(mysqlLocationPushButton, 1, 1);
    setLayout(layout);
}

int PathOnlyPage::nextId() const
{
    return installWizard::Page_Conclusion;
}

void PathOnlyPage::locateMySQLFile()
{
    QString mysqlLocation;
    mysqlLocation = QFileDialog::getOpenFileName(0, "Select File", "", "MySQL Settings (Mameri.mysql.ini)");
    mysqlLocationLineEdit->setText(mysqlLocation);
}




MySQLPage::MySQLPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("MySQL DB Connection"));
    setSubTitle(tr("Please provide the MySQL DB connection details:"));

    mysqlHostLabel = new QLabel(tr("MySQL Host:"));
    mysqlHostLineEdit = new QLineEdit;
    mysqlHostLineEdit->setText("localhost");
    mysqlHostLabel->setBuddy(mysqlHostLineEdit);

    mysqlPortLabel = new QLabel(tr("MySQL Port:"));
    mysqlPortLineEdit = new QLineEdit;
    mysqlPortLineEdit->setText("3306");
    mysqlPortLabel->setBuddy(mysqlPortLineEdit);

    mysqlDatabaseLabel = new QLabel(tr("MySQL DB Name:"));
    mysqlDatabaseLineEdit = new QLineEdit;
    mysqlDatabaseLabel->setBuddy(mysqlDatabaseLineEdit);

    mysqlUserLabel = new QLabel(tr("MySQL User Name:"));
    mysqlUserLineEdit = new QLineEdit;
    mysqlUserLabel->setBuddy(mysqlUserLineEdit);

    mysqlPasswordLabel = new QLabel(tr("MySQL Password:"));
    mysqlPasswordLineEdit = new QLineEdit;
    mysqlPasswordLineEdit->setEchoMode(QLineEdit::Password);
    mysqlPasswordLabel->setBuddy(mysqlPasswordLineEdit);

    mysqlPathLabel = new QLabel(tr("Store Connection File in:"));
    mysqlPathLineEdit = new QLineEdit;
    mysqlPathLabel->setBuddy(mysqlPathLineEdit);

    mysqlDBTestLabel = new QLabel();

    mysqlPathPushButton = new QPushButton(tr("Select Folder"));;
    connect(mysqlPathPushButton, SIGNAL(clicked()), this, SLOT(locateMySQLPath()));

    // Check DB Connection
    connect(mysqlHostLineEdit,      SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(mysqlPortLineEdit,      SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(mysqlDatabaseLineEdit,  SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(mysqlUserLineEdit,      SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(mysqlPasswordLineEdit,  SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));

    registerField("mysqlHost",      mysqlHostLineEdit);
    registerField("mysqlPort",      mysqlPortLineEdit);
    registerField("mysqlDatabase*", mysqlDatabaseLineEdit);
    registerField("mysqlUser*",     mysqlUserLineEdit);
    registerField("mysqlPassword*", mysqlPasswordLineEdit);
    registerField("mysqlPath*",     mysqlPathLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(mysqlHostLabel, 0, 0);
    layout->addWidget(mysqlHostLineEdit, 0, 1);
    layout->addWidget(mysqlPortLabel, 1, 0);
    layout->addWidget(mysqlPortLineEdit, 1, 1);
    layout->addWidget(mysqlDatabaseLabel, 2, 0);
    layout->addWidget(mysqlDatabaseLineEdit, 2, 1);
    layout->addWidget(mysqlUserLabel, 3, 0);
    layout->addWidget(mysqlUserLineEdit, 3, 1);
    layout->addWidget(mysqlPasswordLabel, 4, 0);
    layout->addWidget(mysqlPasswordLineEdit, 4, 1);
    layout->addWidget(mysqlPathLabel, 5, 0);
    layout->addWidget(mysqlPathLineEdit, 5, 1);
    layout->addWidget(mysqlPathPushButton, 5, 2);
    layout->addWidget(mysqlDBTestLabel, 7, 1);
    setLayout(layout);
}

int MySQLPage::nextId() const
{
    return installWizard::Page_Schema;
}

void MySQLPage::locateMySQLPath()
{
    QString mysqlPath;
    mysqlPath = QFileDialog::getExistingDirectory(0, "Select Folder", "", QFileDialog::ShowDirsOnly);
    mysqlPathLineEdit->setText(mysqlPath);
}

bool MySQLPage::isComplete() const
{
    QString testMysqlHost       = mysqlHostLineEdit->text();
    QString testMysqlPortStr    = mysqlPortLineEdit->text();
    int     testMysqlPort       = testMysqlPortStr.toInt();
    QString testMysqlDatabase   = mysqlDatabaseLineEdit->text();
    QString testMysqlUser       = mysqlUserLineEdit->text();
    QString testMysqlPassword   = mysqlPasswordLineEdit->text();
    QFileInfo testMysqlPath       = mysqlPathLineEdit->text();

    QSqlDatabase dbTest = QSqlDatabase::addDatabase("QMYSQL", "testConn");
    dbTest.setHostName      (testMysqlHost);
    dbTest.setPort          (testMysqlPort);
    dbTest.setDatabaseName  (testMysqlDatabase);
    dbTest.setUserName      (testMysqlUser);
    dbTest.setPassword      (testMysqlPassword);

    dbTest.setConnectOptions();

    if(dbTest.open())
    {
        dbTest.close();
        mysqlDBTestLabel->setText(tr("DB connection ok."));
        QSqlDatabase::removeDatabase("testConn");
        if(testMysqlPath.isDir())
        {
            return true;
        } else {
            return false;
        }
    } else {
        mysqlDBTestLabel->setText("");
        QSqlDatabase::removeDatabase("testConn");
        return false;
    }
}


SchemaPage::SchemaPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("MySQL Schema"));

    topLabel = new QLabel(tr("Chose whether you also want to setup the MySQL tables<br>"
                             "- Yes, the tables will also be setup<br>"
                             "- No, only the MySQL Connection fille will be created"));
    topLabel->setWordWrap(true);

    addSchemaRadioButton = new QRadioButton(tr("Yes"));
    skipSchemaRadioButton = new QRadioButton(tr("No, skip tables setup"));
    addSchemaRadioButton->setChecked(true);
    schemaLineEdit = new QLineEdit;
    schemaLineEdit->setText("addSchema");

    connect(addSchemaRadioButton, SIGNAL(clicked()), this, SLOT(addSchemaSlot()));
    connect(skipSchemaRadioButton, SIGNAL(clicked()), this, SLOT(skipSchemaSlot()));

    registerField("mysqlSchema",     schemaLineEdit);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(addSchemaRadioButton);
    layout->addWidget(skipSchemaRadioButton);
    setLayout(layout);
}

int SchemaPage::nextId() const
{
    if (addSchemaRadioButton->isChecked())
    {
        return installWizard::Page_Admin;
    } else {
        return installWizard::Page_Conclusion;
    }
}

void SchemaPage::addSchemaSlot()
{
    schemaLineEdit->setText("addSchema");
}

void SchemaPage::skipSchemaSlot()
{
    schemaLineEdit->setText("skipSchema");
}




AdminPage::AdminPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Mameri Admin User"));
    setSubTitle(tr("Setup an admin user for your Mameri installation:"));

    adminUserLabel = new QLabel(tr("Admin User Name:"));
    adminUserLineEdit = new QLineEdit;
    adminUserLabel->setBuddy(adminUserLineEdit);

    adminPasswordLabel = new QLabel(tr("Password:"));
    adminPasswordLineEdit = new QLineEdit;
    adminPasswordLineEdit->setEchoMode(QLineEdit::Password);
    adminPasswordLabel->setBuddy(adminPasswordLineEdit);

    adminPasswordRepeatLabel = new QLabel(tr("Repeat Password:"));
    adminPasswordRepeatLineEdit = new QLineEdit;
    adminPasswordRepeatLineEdit->setEchoMode(QLineEdit::Password);
    adminPasswordRepeatLabel->setBuddy(adminPasswordRepeatLineEdit);

    passwordMatchLabel = new QLabel();

    connect(adminUserLineEdit, SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(adminPasswordLineEdit, SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));
    connect(adminPasswordRepeatLineEdit, SIGNAL(selectionChanged()), this, SIGNAL(completeChanged()));

    registerField("mysqlAdminUser*",             adminUserLineEdit);
    registerField("mysqlAdminPassword*",         adminPasswordLineEdit);
    registerField("mysqlAdminPasswordRepeat*",   adminPasswordRepeatLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(adminUserLabel, 0, 0);
    layout->addWidget(adminUserLineEdit, 0, 1);
    layout->addWidget(adminPasswordLabel, 1, 0);
    layout->addWidget(adminPasswordLineEdit, 1, 1);
    layout->addWidget(adminPasswordRepeatLabel, 2, 0);
    layout->addWidget(adminPasswordRepeatLineEdit, 2, 1);
    layout->addWidget(passwordMatchLabel, 3, 1);

    setLayout(layout);

}

bool AdminPage::isComplete() const
{
    QString testAdminUser = adminUserLineEdit->text();
    QString testAdminPassword = adminPasswordLineEdit->text();
    QString testAdminPasswordRepeat = adminPasswordRepeatLineEdit->text();

    if( (testAdminPassword == testAdminPasswordRepeat) && (!testAdminPassword.isEmpty()) )
    {
        passwordMatchLabel->setText(tr("Passwords do match."));

        if(!testAdminUser.isEmpty())
        {
            return true;
        } else {
            return false;
        }
    } else {
        passwordMatchLabel->setText("");
        return false;
    }
}

int AdminPage::nextId() const
{
    return installWizard::Page_Conclusion;
}


ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Setup Complete"));

    finishLabel = new QLabel;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(finishLabel);
    setLayout(layout);
}

void ConclusionPage::initializePage()
{
    // Get all the supplied info
    QString myLocation              = field("mysqlLocation").toString();
    QString myHost                  = field("mysqlHost").toString();
    int myPort                      = field("mysqlPort").toInt();
    QString myDatabase              = field("mysqlDatabase").toString();
    QString myUser                  = field("mysqlUser").toString();
    QString myPassword              = field("mysqlPassword").toString();
    QString myPath                  = field("mysqlPath").toString();
    QString mySchema                = field("mysqlSchema").toString();
    QString myAdminUser             = field("mysqlAdminUser").toString();
    QString myAdminPassword         = field("mysqlAdminPassword").toString();
    QString myAdminPasswordRepeat   = field("mysqlAdminPasswordRepeat").toString();

    QString progress = "The install wizard did the following things:<br>";

    // Check if the mysql connections file has to be written
    if(!myPath.isEmpty())
    {
        // Store the path to the mysql settings file for current user
        QString myFileName   = "/Mameri.mysql.ini";
        myPath.append(myFileName);
        QSettings myFileSettings(myPath, QSettings::IniFormat);
        myFileSettings.beginGroup("MySQL");
        myFileSettings.setValue("hostname",    myHost);
        myFileSettings.setValue("port",        myPort);
        myFileSettings.setValue("dbname",      myDatabase);
        myFileSettings.setValue("username",    myUser);
        myFileSettings.setValue("password",    myPassword);
        myFileSettings.endGroup();
        QString myConfig   ="<br>- wrote the MySQL Config Settings";

        QSettings settingLocal("Mameri", "mameri");
        settingLocal.beginGroup("MySQLPath");
        settingLocal.setValue("location",    myPath);
        settingLocal.endGroup();

        progress.append(myConfig);
    }

    // Check if MySQL Schema needs to be loaded
    QString mySchemaCheck = "addSchema";
    if(mySchema == mySchemaCheck)
    {
        // Open DB connection
        QSqlDatabase dbInstall = QSqlDatabase::addDatabase("QMYSQL", "installConn");
        dbInstall.setHostName      (myHost);
        dbInstall.setPort          (myPort);
        dbInstall.setDatabaseName  (myDatabase);
        dbInstall.setUserName      (myUser);
        dbInstall.setPassword      (myPassword);

        dbInstall.setConnectOptions();

        if(dbInstall.open())
        {
            QSqlQuery qry;

            // Load the Schema into the db
            QFile file("../mameri.sql");
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
            QTextStream in(&file);
            QString DBSQLCommands = in.readAll();
            file.close();
            qry.prepare(DBSQLCommands);
            qry.exec();

            // Create salt and hash password
            QString salt = QUuid::createUuid().toString();
            myAdminPassword.append(salt);
            QByteArray hashed = QCryptographicHash::hash(myPassword.toUtf8(), QCryptographicHash::Sha3_256);
            QString hashedPassword(hashed.toHex().constData());

            // Add Admin user
            QString sql = "INSER INTO users SET login = :login, password = :password, role = 'Admin', salt = :salt ;";
            qry.bindValue(":login", myAdminUser);
            qry.bindValue(":password", hashedPassword);
            qry.bindValue(":salt", salt);
            qry.prepare(sql);
            qry.exec();
        }
        dbInstall.close();
        QSqlDatabase::removeDatabase("installConn");

        QString myConfig   ="<br>- loaded the Schema into the Database";
        progress.append(myConfig);
        QString myAdmin   ="<br>- loaded the Schema into the Database";
        progress.append(myAdmin);
    }

    // Check if pat to the MySQL Config Settings file was given
    if(myPath.isEmpty())
    {
        QSettings settingLocal("Mameri", "mameri");
        settingLocal.beginGroup("MySQLPath");
        settingLocal.setValue("location",    myLocation);
        settingLocal.endGroup();
    }

    QString myLocal   ="<br>- set path to the MySQL Config Settings file";
    progress.append(myLocal);

    finishLabel->setText(progress);

}


int ConclusionPage::nextId() const
{
    return -1;
}


