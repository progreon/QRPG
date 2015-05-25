#include "mainwindow.h"
#include <QApplication>

#include <assert.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(files);
    QApplication a(argc, argv);

    // TODO: open the project here instead of in the QRPGGame class!

    MainWindow w;
    w.show();
    w.startGame();

    return a.exec();
}
