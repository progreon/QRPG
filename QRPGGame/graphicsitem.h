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

#ifndef QRPG_GRAPHICSITEM_H
#define QRPG_GRAPHICSITEM_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QRectF>
#include <QPointF>

namespace QRPG {

class GraphicsItem : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsItem(QObject *parent = 0);
    ~GraphicsItem();
    virtual QRectF boundingRect() const = 0;
    virtual QPointF pos() const;
    virtual void moveBy(qreal dx, qreal dy);
    virtual const QPixmap *pixmap() const = 0;
//    virtual const QImage *image() const = 0;
    virtual QRectF sceneBoundingRect() const;
    virtual void setPos(qreal x, qreal y);

signals:

public slots:
    virtual void doTick() = 0;

private:
    QPointF _pos;

};

}

#endif // QRPG_GRAPHICSITEM_H
