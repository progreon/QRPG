#include "mainwindow.h"
#include <QApplication>

#include "qrpgdatabase.h"
#include <iostream>
#include <assert.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRPGDao::QRPGDatabase *dao = QRPGDao::newDao(QRPGDao::FILE);
    assert(dao != NULL);
    std::cout << dao->getInfo().toStdString() << std::endl;
    MainWindow w;
    w.show();

    return a.exec();
}
