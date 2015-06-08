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

#ifndef QRPG_QRPGSCENE_H
#define QRPG_QRPGSCENE_H

#include <QObject>
//#include <QMutex>
//#include <QMutexLocker>
#include <QPixmap>
#include <QImage>
#include <QPointF>
#include <QMap>
#include <QSet>
#include <QVector>
#include "graphicsitem.h"

namespace QRPG {

class QRPGScene : public QObject
{
    Q_OBJECT
public:
    explicit QRPGScene(QObject *parent = 0);
    ~QRPGScene();
    //TODO: Needs optimisation!
    //TODO: Return rendered "boundingRect"
    /**
     * @brief render Renders its items onto a given pixmap
     * @param screen The pixmap to render on
     * @param point The top-left corner of the scene that should be rendered
     */
    virtual void render(QPixmap *screen, const QPointF &pos);
    /**
     * @brief addGraphicsItem Add an item to the scene
     * @param item The item to add to the scene
     * @param layer On which layer to add this item (default 0)
     * @return <code>true</code> if the item is new to this scene, <code>false</code> otherwise
     */
    virtual bool addGraphicsItem(GraphicsItem *item, int layer = 0);
    virtual bool deleteGraphicsItem(GraphicsItem *item);

signals:

public slots:
    virtual void doTick();

private:
//    QMutex renderMutex;

    QMap<int, QSet<GraphicsItem *> > itemsPerLayer;
    // TODO: needs optimisation?
    bool itemIsInRect(const QRectF &rect, const GraphicsItem *item) const;
};

}

#endif // QRPG_QRPGSCENE_H
