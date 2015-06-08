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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

#include "model/qrpgproject.h"

MainWindow::MainWindow(QRPGDao::QRPGDatabase *dao, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    dao(dao)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_New_project_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setDirectory(QDir::home());
//    QString fileName = QFileDialog::getOpenFileName(this, "Open", "~", "Folders ()");
    if (dialog.exec()) {
        QString fileName = dialog.selectedFiles().first();
        qDebug() << fileName;
        QDir dir(fileName);
        if (dir.exists()) {
            QString projTitle = "Test Project";
            QString gameTitle = "Test Game";
            QRPGDao::QRPGProject *proj = dao->createNewProject(dir.canonicalPath(), projTitle, gameTitle);
            if (proj != NULL) {
                qDebug() << proj->getProjectFolderURI();
            } else {
                qWarning() << "NULL reference to newly created project: " << projTitle << " in " << dir.absolutePath();
            }
        }
    } else {
        qDebug() << "No folder selected.";
    }
}

void MainWindow::on_action_Open_project_triggered()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::DirectoryOnly);
    dialog.setDirectory(QDir::home());
//    QString fileName = QFileDialog::getOpenFileName(this, "Open", "~", "Folders ()");
    if (dialog.exec()) {
        QString fileName = dialog.selectedFiles().first();
        qDebug() << fileName;
        QDir dir(fileName);
        if (dir.exists()) {
            QRPGDao::QRPGProject *proj = dao->openProjectDir(dir.canonicalPath());
            if (proj != NULL) {
                qDebug() << proj->getProjectFolderURI();
            } else {
                qWarning() << "NULL reference to opened project: " << dir.canonicalPath();
            }
        }
    } else {
        qDebug() << "No folder selected.";
    }
}

void MainWindow::on_action_Close_project_triggered()
{
    // TODO: properly
    dao->closeProject();
}

void MainWindow::on_actionE_xit_triggered()
{
    this->close();
}
