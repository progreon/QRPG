#include "tiles/tileitem.h"
#include <QImage>

QRPG::TileItem::TileItem(QRPG::Sprite *sprite, QObject *parent)
    : GraphicsItem(parent)
    , sprite(sprite)
{
    tileSize = sprite->pixmap()->width();
}

QRPG::TileItem::~TileItem()
{

}

int QRPG::TileItem::getTileSize() const
{
    return tileSize;
}

QRectF QRPG::TileItem::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

const QPixmap *QRPG::TileItem::pixmap() const
{
    return sprite->pixmap();
}

void QRPG::TileItem::doTick()
{
}
