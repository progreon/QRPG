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

#include "qrpgmap.h"
#include "qrpgproject.h"

namespace QRPGDao {

QRPGMap::QRPGMap(QRPGProject *project, int ID, QString name, int width, int height)
    : _project(project)
    , _ID(ID)
    , _name(name)
    , _width(width)
    , _height(height)
{
    tiles.resize(3);
    for (int l = 0; l < 3; l++) { // loop all layers
        tiles[l].resize(width);
        for (int x=0; x<width; x++) { // loop the width
            tiles[l][x].resize(height);
            for (int y=0; y<height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    setSpawn(0, 0);
}

QRPGMap::~QRPGMap()
{
    
}

void QRPGMap::setHeight(int height)
{
    for (int l=0; l<3; l++) { // loop all layers
        for (int x=0; x<_width; x++) { // loop the width
            tiles[l][x].resize(height);
            for (int y=_height; y<height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    _height = height;
}

bool QRPGMap::setSpawn(int x, int y)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    } else {
        _spawn = QPoint(x, y);
        return true;
    }
}

bool QRPGMap::setTile(int layer, int x, int y, QRPGTile *tile)
{
    if (layer < 0 || layer >= 3 || x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    } else {
        tiles[layer][x][y] = tile;
        return true;
    }
}

void QRPGMap::setWidth(int width)
{
    for (int l = 0; l < 3; l++) { // loop all layers
        tiles[l].resize(width);
        for (int x=_width; x<width; x++) { // loop the width
            tiles[l][x].resize(_height);
            for (int y=0; y<_height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    _width = width;
}

const QRPGTile *QRPGMap::tile(int layer, int x, int y)
{
    if (layer < 0 || layer >= 3 || x < 0 || x >= _width || y < 0 || y >= _height) {
        return NULL;
    } else {
        return tiles[layer][x][y];
    }
}

} // namespace QRPGDao

