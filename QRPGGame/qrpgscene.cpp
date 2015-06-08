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

#include "qrpgscene.h"
#include <QPainter>
#include <QDebug>

QRPG::QRPGScene::QRPGScene(QObject *parent) : QObject(parent)
{

}

QRPG::QRPGScene::~QRPGScene()
{

}

void QRPG::QRPGScene::render(QPixmap *screen, const QPointF &pos)
{
//    QMutexLocker locker(&renderMutex);
    QRectF screenRect(pos.x(), pos.y(), screen->rect().width(), screen->rect().height());
    if (!screen->isNull()) {
        QPainter painter(screen);
        painter.fillRect(screen->rect(), Qt::black);
        foreach (QSet<GraphicsItem *> layerItems, itemsPerLayer.values()) {
            foreach (GraphicsItem *item, layerItems) {
                // if (itemIsInRect(screen->rect(), item)) {
                if (itemIsInRect(screenRect, item)) {
                    painter.drawPixmap(item->pos() - pos, *(item->pixmap()), item->boundingRect());
                }
            }
        }
        painter.end();
    }
}

bool QRPG::QRPGScene::addGraphicsItem(GraphicsItem *item, int layer)
{
    bool exists = false;
    foreach (QSet<GraphicsItem *> set, itemsPerLayer) {
        if (set.contains(item)) {
            exists = true;
        }
    }
    if (!exists) {
        itemsPerLayer[layer].insert(item);
    }
    return !exists;
}

bool QRPG::QRPGScene::deleteGraphicsItem(QRPG::GraphicsItem *item)
{
    bool exists = false;
    foreach (QSet<GraphicsItem *> set, itemsPerLayer) {
        if (set.contains(item)) {
            exists = true;
            set.remove(item);
        }
    }
    return exists;
}

void QRPG::QRPGScene::doTick()
{
    foreach (QSet<GraphicsItem *> set, itemsPerLayer) {
        foreach (GraphicsItem *item, set) {
            item->doTick();
        }
    }
}

bool QRPG::QRPGScene::itemIsInRect(const QRectF &rect, const GraphicsItem *item) const
{
    QRectF itemRect(item->pos(), QSizeF(item->boundingRect().width(), item->boundingRect().height()));
    return rect.intersects(itemRect);
}

