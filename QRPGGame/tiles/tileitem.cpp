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

#include "tiles/tileitem.h"
#include <QImage>

QRPG::TileItem::TileItem(QRPG::Sprite *sprite, int tileSize, QObject *parent)
    : GraphicsItem(parent)
    , sprite(sprite)
    , _tileSize(tileSize)
{

}

QRPG::TileItem::~TileItem()
{

}

int QRPG::TileItem::tileSize() const
{
    return _tileSize;
}

QRectF QRPG::TileItem::boundingRect() const
{
    return QRectF(0, 0, _tileSize, _tileSize);
}

const QPixmap *QRPG::TileItem::pixmap() const
{
    return sprite->pixmap();
}

void QRPG::TileItem::doTick()
{
}
