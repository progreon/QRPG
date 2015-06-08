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

#ifndef QRPGDAO_QRPGMAP_H
#define QRPGDAO_QRPGMAP_H

#include "qrpgtile.h"
#include <QVector>
#include <QPoint>

namespace QRPGDao {

class QRPGProject;

class QRPGMap
{
public:
    QRPGMap(QRPGProject *project, int ID, QString name, int width = 20, int height = 20);
    ~QRPGMap();
    int height() const {return _height;}
    int ID() const {return _ID;}
    QString name() const {return _name;}
    const QRPGProject *project() const {return _project;}
    void setHeight(int height);
    bool setSpawn(int x, int y);
    bool setTile(int layer, int x, int y, QRPGTile *tile);
    void setWidth(int width);
    QPoint spawn() const {return _spawn;}
    const QRPGTile *tile(int layer, int x, int y);
    int width() const {return _width;}

private:
    const QRPGProject *_project;
    const int _ID;
    QString _name;
    int _width, _height;
    // different tiles on 3 layers (base, buildings, extra)
    // the original tiles are kept in the project object
    QVector<QVector<QVector<QRPGTile *> > > tiles; // tiles[layer][x][y]
    // player spawn
    QPoint _spawn;
    // NPCs
    // map areas
    // events
    // ...


};

} // namespace QRPGDao

#endif // QRPGDAO_QRPGMAP_H
