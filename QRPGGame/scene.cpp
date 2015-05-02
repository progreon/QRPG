#include "scene.h"
#include <QPainter>
#include <QDebug>

Scene::Scene(QObject *parent) : QObject(parent)
{

}

Scene::~Scene()
{

}

void Scene::render(QPixmap *screen, const QPointF &pos) const
{
    QRectF screenRect(pos.x(), pos.y(), screen->rect().width(), screen->rect().height());
    if (!screen->isNull()) {
        QPainter painter(screen);
        painter.fillRect(screen->rect(), Qt::black);
        for (int i = 0; i < usedLayers.length(); i++) {
            foreach (GraphicsItem *item, itemsPerLayer.value(usedLayers.at(i))) {
                // if (itemIsInRect(screen->rect(), item)) {
                if (itemIsInRect(screenRect, item)) {
                    painter.drawPixmap(item->pos() - pos, *(item->pixmap()), item->boundingRect());
                }
            }
        }
        painter.end();
    }
}

bool Scene::addGraphicsItem(GraphicsItem *item, int layer)
{
    bool exists = false;
    foreach (QSet<GraphicsItem *> set, itemsPerLayer) {
        if (set.contains(item)) {
            exists = true;
        }
    }
    if (!exists) {
        if (!usedLayers.contains(layer)) {
            usedLayers.push_back(layer);
            std::sort(usedLayers.begin(), usedLayers.end());
        }
        itemsPerLayer[layer].insert(item);
    }
    return !exists;
}

void Scene::doTick()
{
    foreach (QSet<GraphicsItem *> set, itemsPerLayer) {
        foreach (GraphicsItem *item, set) {
            item->doTick();
        }
    }
}

bool Scene::itemIsInRect(const QRectF &rect, const GraphicsItem *item) const
{
    QRectF itemRect(item->pos(), QSizeF(item->boundingRect().width(), item->boundingRect().height()));
    return rect.intersects(itemRect);
}

