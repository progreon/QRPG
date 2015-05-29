#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

#include <assert.h>

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(files);
    QApplication a(argc, argv);

    // TODO: open the project here instead of in the QRPGGame class!
    QRPGDao::QRPGDatabase *dao = QRPGDao::newDao();
    QRPGDao::QRPGProject *project = NULL;
    if (argc > 1) {
        // argv[1] shall be the project/game folder!
        QString gameFolderURI(argv[1]);
        QDir gameFolder(gameFolderURI);
        if (gameFolder.exists()) {
            project = dao->openProjectDir(gameFolderURI);
        }
    }
    if (project == NULL) {
        project = dao->openDummyProject();
    }
    MainWindow w(project);
    w.show();
    w.startGame();

    return a.exec();
}
