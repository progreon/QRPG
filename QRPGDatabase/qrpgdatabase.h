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

#ifndef QRPGDATABASE_H
#define QRPGDATABASE_H

#include <QString>

namespace QRPGDao {

class QRPGProject;

class QRPGDatabase
{

public:
    virtual void closeProject() = 0;
    virtual QRPGProject *createNewProject(const QString &projectLocationURI, const QString &projectTitle, const QString &gameTitle) = 0;
    virtual QString info() const = 0; // Tells you what kind of Dao this is
    virtual QRPGProject *openDummyProject() = 0;
    virtual QRPGProject *openProjectDir(const QString &projectDirURI) = 0;

protected:
    QRPGProject *newProject(const QString &projectDirURI, const QString &projectTitle, const QString &gameTitle);
    void setProjectTileSize(QRPGProject *project, int tileSize);
};

enum DaoType
{
    FILE
};

QRPGDatabase *newDao();

} // namespace QRPGDao

#endif // QRPGDATABASE_H
