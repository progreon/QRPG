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

#include "graphicsitem.h"

QRPG::GraphicsItem::GraphicsItem(QObject *parent) : QObject(parent)
{

}

QRPG::GraphicsItem::~GraphicsItem()
{

}

QPointF QRPG::GraphicsItem::pos() const
{
    return _pos;
}

void QRPG::GraphicsItem::moveBy(qreal dx, qreal dy)
{
    _pos.setX(_pos.x() + dx);
    _pos.setY(_pos.y() + dy);
}

QRectF QRPG::GraphicsItem::sceneBoundingRect() const
{
    return QRectF(_pos.x(), _pos.y(), boundingRect().width(), boundingRect().height());
}

void QRPG::GraphicsItem::setPos(qreal x, qreal y)
{
    _pos.setX(x);
    _pos.setY(y);
}

