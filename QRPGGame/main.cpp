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
