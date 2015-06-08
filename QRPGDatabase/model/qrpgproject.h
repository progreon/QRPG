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

#ifndef QRPGDAO_QRPGPROJECT_H
#define QRPGDAO_QRPGPROJECT_H


#include <QString>
#include <QMap>
#include "../qrpgdatabase.h"
#include "../impl/qrpgfiledao.h"
#include "qrpgsprite.h"
#include "qrpgtile.h"
#include "qrpgmap.h"

namespace QRPGDao {
class QRPGProject
{
    friend class QRPGDatabase;
//    friend QRPGProject *QRPGDatabase::createNewProject(const QDir&, QString, QString);
public:
    ~QRPGProject();
    bool addNewMap(QRPGMap *map);
    bool addNewSprite(QRPGSprite *sprite);
    bool addNewTile(QRPGTile *tile);
    const QRPGDatabase *dao() const {return _dao;}
    QString gameTitle() const {return _gameTitle;}
    QString getProjectFolderURI() const {return _projectFolderURI;}
    QString getProjectTitle() const {return _projectTitle;}
    QMap<int, QRPGMap *> maps() const {return _maps;}
    void setProjectTitle(QString projectTitle);
    void setGameTitle(QString gameTitle);
    QMap<int, QRPGSprite *> sprites() const {return _sprites;}
    QMap<int, QRPGTile *> tiles() const {return _tiles;}
    int tileSize() const {return _tileSize;}

private:
    QRPGProject(QRPGDatabase *dao, QString projectFolderURI, QString projectTitle, QString gameTitle);
    void setTileSize(int tileSize) {_tileSize = tileSize;}

    const QRPGDatabase *_dao; /*!< The dao used in the application, do NOT delete this pointer!*/
    QString _projectFolderURI;
    QString _projectTitle;
    QString _gameTitle;
    int _tileSize;

    QMap<int, QRPGSprite *> _sprites; // spriteID => sprite*
    QMap<int, QRPGTile *> _tiles; // tileID => tile*
    QMap<int, QRPGMap *> _maps; // mapID => map*
};

} // namespace QRPGDao

#endif // QRPGDAO_QRPGPROJECT_H
