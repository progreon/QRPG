/*
This file is part of the QRPG project
Copyright (C) 2015  Marco Willems

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
