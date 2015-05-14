#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
//#include "loaders/qrpgmaploader.h"
//#include "qrpgdatabase.h"
//#include "model/qrpgproject.h"

#include <assert.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(files);
    QApplication a(argc, argv);
//    QRPGDao::QRPGDatabase *dao = QRPGDao::newDao(QRPGDao::FILE);
//    QRPGDao::QRPGProject *dummyProject = dao->openDummyProject();
//    qDebug() << dao->getInfo();
//    QRPG::QRPGMapLoader mapLoader(NULL);
//    mapLoader.newExampleMap();

    MainWindow w;
    w.show();

    return a.exec();
//    return 0;
}
