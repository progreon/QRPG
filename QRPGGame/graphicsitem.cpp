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

