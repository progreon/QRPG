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
