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
            QString projTitle = "TestProject";
            QString gameTitle = "TestGame";
            QRPGDao::QRPGProject *proj = dao->createNewProject(dir, projTitle, gameTitle);
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
