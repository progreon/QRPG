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

