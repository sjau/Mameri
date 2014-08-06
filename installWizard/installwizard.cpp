#include "installwizard.h"
#include "ui_installwizard.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QObject>

installWizard::installWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::installWizard)
{
    setPage(Page_Intro, new IntroPage);
    setPage(Page_MySQL, new MySQLPage);
    setPage(Page_PathOnly, new PathOnlyPage);
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
                             "- Use 'Install Mameri Server' if there's isn't anything setup yet."));
    topLabel->setWordWrap(true);

    pathRadioButton = new QRadioButton(tr("&Locate MySQL Config File"));
    fullRadioButton = new QRadioButton(tr("&Install Mameri Server"));
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

    pathLabel = new QLabel(tr("MySQL Config File Location:"));
    pathLineEdit = new QLineEdit;
    pathLabel->setBuddy(pathLineEdit);

    pathPushButton = new QPushButton(tr("Select MySQL Config File"));;
    connect(pathPushButton, SIGNAL(clicked()), this, SLOT(selectMySQLFile()));

    registerField("register.mysqlPath*", pathLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(pathLabel, 0, 0);
    layout->addWidget(pathLineEdit, 0, 1);
    layout->addWidget(pathPushButton, 1, 1);
    setLayout(layout);
}

int PathOnlyPage::nextId() const
{
    return installWizard::Page_Conclusion;
}

void PathOnlyPage::selectMySQLFile() {
    QString mysqlFileName;
    mysqlFileName = QFileDialog::getOpenFileName(0, "Select File", "", "MySQL Settings (Mameri.mysql.ini)");
}


MySQLPage::MySQLPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Register Your Copy of <i>Super Product One</i>&trade;"));
    setSubTitle(tr("If you have an upgrade key, please fill in "
                   "the appropriate field."));

    nameLabel = new QLabel(tr("N&ame:"));
    nameLineEdit = new QLineEdit;
    nameLabel->setBuddy(nameLineEdit);

    upgradeKeyLabel = new QLabel(tr("&Upgrade key:"));
    upgradeKeyLineEdit = new QLineEdit;
    upgradeKeyLabel->setBuddy(upgradeKeyLineEdit);

    registerField("register.name*", nameLineEdit);
    registerField("register.upgradeKey", upgradeKeyLineEdit);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameLineEdit, 0, 1);
    layout->addWidget(upgradeKeyLabel, 1, 0);
    layout->addWidget(upgradeKeyLineEdit, 1, 1);
    setLayout(layout);
}

int MySQLPage::nextId() const
{
    return installWizard::Page_Conclusion;
}

ConclusionPage::ConclusionPage(QWidget *parent)
    : QWizardPage(parent)
{
    setTitle(tr("Complete Your Registration"));
    setPixmap(QWizard::WatermarkPixmap, QPixmap(":/images/watermark.png"));

    bottomLabel = new QLabel;
    bottomLabel->setWordWrap(true);

    agreeCheckBox = new QCheckBox(tr("I agree to the terms of the license"));

    registerField("conclusion.agree*", agreeCheckBox);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(bottomLabel);
    layout->addWidget(agreeCheckBox);
    setLayout(layout);
}

int ConclusionPage::nextId() const
{
    return -1;
}

void ConclusionPage::initializePage()
{
    QString licenseText;

    if (wizard()->hasVisitedPage(installWizard::Page_MySQL)) {
        licenseText = tr("<u>Evaluation License Agreement:</u> "
                         "You can use this software for 30 days and make one "
                         "backup, but you are not allowed to distribute it.");
    } else if (wizard()->hasVisitedPage(installWizard::Page_PathOnly)) {
        licenseText = tr("<u>First-Time License Agreement:</u> "
                         "You can use this software subject to the license "
                         "you will receive by email.");
    } else {
        licenseText = tr("<u>Upgrade License Agreement:</u> "
                         "This software is licensed under the terms of your "
                         "current license.");
    }
    bottomLabel->setText(licenseText);
}

