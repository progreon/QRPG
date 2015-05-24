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
