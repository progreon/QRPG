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

#include "mapscene.h"
#include <QDebug>

QRPG::MapScene::MapScene(int width, int height, QObject *parent) : QRPGScene(parent), width(width), height(height)
{
    tiles.resize(width);
    for (int i = 0; i < width; i++) {
        tiles[i].resize(height);
    }
    ticksPassed = 0;
}

QRPG::MapScene::~MapScene()
{
    for (int i = 0; i < tiles.length(); i++) {
        for (int j = 0; j < tiles[i].length(); j++) {
            delete tiles[i][j];
        }
    }
}

QRPG::TileItem *QRPG::MapScene::getTile(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[x][y];
    } else {
        return NULL;
    }
}

void QRPG::MapScene::setTileItem(int x, int y, QRPG::TileItem *tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
//        deleteGraphicsItem(tiles[x][y]);
//        delete tiles[x][y];
        tile->setPos(x * tile->tileSize(), y * tile->tileSize());
        tiles[x][y] = tile;
        addGraphicsItem(tile);
    }
}

void QRPG::MapScene::doTick()
{

}
