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

#include "qrpgdatabase.h"
#include "impl/qrpgfiledao.h"
#include "model/qrpgproject.h"

namespace QRPGDao {

QRPGDatabase *newDao()
{
    return new QRPGDao::Impl::QRPGFileDao();
}

QRPGProject *QRPGDatabase::newProject(const QString &projectDirURI, const QString &projectTitle, const QString &gameTitle)
{
    return new QRPGProject(this, projectDirURI, projectTitle, gameTitle);
}

void QRPGDatabase::setProjectTileSize(QRPGProject *project, int tileSize)
{
    if (project != NULL && tileSize != 0) {
        project->setTileSize(tileSize);
    }
}

} // namespace QRPGDao

