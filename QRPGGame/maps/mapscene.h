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

#ifndef QRPG_MAPSCENE_H
#define QRPG_MAPSCENE_H

#include <QVector>
#include "../tiles/tileitem.h"
#include "../qrpgscene.h"

namespace QRPG {

class MapScene : public QRPGScene
{
public:
    MapScene(int width = 20, int height = 20, QObject *parent = 0);
    ~MapScene();
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    TileItem *getTile(int x, int y) const;
    void setTileItem(int x, int y, TileItem *tile);

private:
    const int width, height;
    QVector<QVector<TileItem *> > tiles;
    int ticksPassed;

    // Scene interface
public slots:
    void doTick();
};

}

#endif // QRPG_MAPSCENE_H
