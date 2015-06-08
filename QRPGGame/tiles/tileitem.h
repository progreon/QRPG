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

#ifndef QRPG_TILEITEM_H
#define QRPG_TILEITEM_H

#include <QPixmap>
#include <QImage>
#include "../graphicsitem.h"
#include "../sprites/sprite.h"

namespace QRPG {

class TileItem : public GraphicsItem
{
public:
    TileItem(Sprite *sprite, int tileSize, QObject *parent = 0);
    ~TileItem();
    int tileSize() const;

private:
    Sprite *sprite;
    int _tileSize;

    // GraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual const QPixmap *pixmap() const;
//    virtual const QImage *image() const;

public slots:
    virtual void doTick();
};

}

#endif // QRPG_TILEITEM_H
