#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qrpgdatabase.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QRPGDao::QRPGDatabase *dao, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_action_New_project_triggered();

    void on_action_Open_project_triggered();

    void on_action_Close_project_triggered();

    void on_actionE_xit_triggered();

private:
    Ui::MainWindow *ui;
    QRPGDao::QRPGDatabase *dao;
};

#endif // MAINWINDOW_H
