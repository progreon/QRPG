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

#ifndef QRPGDAO_IMPL_QRPGFILEDAO_H
#define QRPGDAO_IMPL_QRPGFILEDAO_H

#include <QDir>
#include "qrpgdatabase.h"

namespace QRPGDao {
namespace Impl {

class QRPGFileDao : public QRPGDao::QRPGDatabase
{
public:
    friend QRPGDao::QRPGDatabase *QRPGDao::newDao();
    ~QRPGFileDao();

private:
    static const QString relProjectFile;

    QRPGFileDao();
    QRPGDao::QRPGProject *currentProject;
    bool importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI);
    bool importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI);
    void initMapsDir(const QDir &mapsDir);
    void initProjectFile(const QDir &projectDir, const QString &gameTitle, int tileSize);
    bool initProjectFromFile(QRPGDao::QRPGProject *project);
    void initTilesDir(const QDir &tilesDir);

    // QRPGDatabase interface
public:
    QRPGDao::QRPGProject *createNewProject(const QString &projectLocationURI, const QString &projectTitle, const QString &gameTitle);
    QRPGDao::QRPGProject *openDummyProject();
    QRPGDao::QRPGProject *openProjectDir(const QString &projectDirURI);
    void closeProject();
    QString info() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGFILEDAO_H
