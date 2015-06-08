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

#include "qrpgproject.h"

namespace QRPGDao {

//const int QRPGProject::_tileSize = 8;

QRPGProject::QRPGProject(QRPGDatabase *dao, QString projectFolderURI, QString projectTitle, QString gameTitle)
    : _dao(dao)
    , _projectFolderURI(projectFolderURI)
    , _projectTitle(projectTitle)
    , _gameTitle(gameTitle)
{
    _tileSize = 1;
}

QRPGProject::~QRPGProject()
{
    foreach (QRPGSprite *sprite, _sprites.values()) {
        delete sprite;
    }
    foreach (QRPGTile *tile, _tiles.values()) {
        delete tile;
    }
    foreach (QRPGMap *map, _maps.values()) {
        delete map;
    }
}

bool QRPGProject::addNewMap(QRPGMap *map)
{
    if (_maps.contains(map->ID())) {
        return false;
    } else {
        _maps.insert(map->ID(), map);
        return true;
    }
}

bool QRPGProject::addNewSprite(QRPGSprite *sprite)
{
    if (_sprites.contains(sprite->ID())) {
        return false;
    } else {
        _sprites.insert(sprite->ID(), sprite);
        return true;
    }
}

bool QRPGProject::addNewTile(QRPGTile *tile)
{
    if (_tiles.contains(tile->ID())) {
        return false;
    } else {
        _tiles.insert(tile->ID(), tile);
        return true;
    }
}

void QRPGProject::setProjectTitle(QString projectTitle)
{
    // TODO
    this->_projectTitle = projectTitle;
}

void QRPGProject::setGameTitle(QString gameTitle)
{
    this->_gameTitle = gameTitle;
}

} // namespace QRPGDao

