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

#include "qrpgmaploader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <model/qrpgtile.h>
#include "tiles/tileitem.h"
#include "../qrpggame.h"

namespace QRPG {

QRPGMapLoader::QRPGMapLoader(QRPGGame *game, QObject *parent)
    : QObject(parent)
    , _game(game)
{

}

QRPGMapLoader::~QRPGMapLoader()
{

}

MapScene *QRPGMapLoader::newMap(QRPGDao::QRPGMap *map)
{
    MapScene *mapScene = new MapScene(map->width(), map->height());
    // TODO
    for (int l=0; l<3; l++) {
        for (int x=0; x<map->width(); x++) {
            for (int y=0; y<map->height(); y++) {
                const QRPGDao::QRPGTile *daoTile = map->tile(l, x, y);
                if (daoTile != NULL) {
                    TileItem *tile = new TileItem(_game->sprite(daoTile->sprite()->ID()), map->project()->tileSize(), mapScene);
                    mapScene->setTileItem(x, y, tile);
                }
            }
        }
    }
    return mapScene;
}

} // namespace QRPG

