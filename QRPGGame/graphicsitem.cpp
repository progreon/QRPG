#include "graphicsitem.h"

GraphicsItem::GraphicsItem(QObject *parent) : QObject(parent)
{

}

GraphicsItem::~GraphicsItem()
{

}

QPointF GraphicsItem::pos() const
{
    return _pos;
}

void GraphicsItem::moveBy(qreal dx, qreal dy)
{
    _pos.setX(_pos.x() + dx);
    _pos.setY(_pos.y() + dy);
}

QRectF GraphicsItem::sceneBoundingRect() const
{
    return QRectF(_pos.x(), _pos.y(), boundingRect().width(), boundingRect().height());
}

void GraphicsItem::setPos(qreal x, qreal y)
{
    _pos.setX(x);
    _pos.setY(y);
}

