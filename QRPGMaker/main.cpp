#include "mainwindow.h"
#include <QApplication>

#include "qrpgdatabase.h"
#include <assert.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(files);
    QApplication a(argc, argv);

    QRPGDao::QRPGDatabase *dao = QRPGDao::newDao();
    assert(dao != NULL);
    qDebug() << dao->info();
    MainWindow w(dao);
    w.show();

    return a.exec();
}
