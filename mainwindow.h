#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSqlDatabase db, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionBenutzereinstellungen_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
