#include "tiles/tileitem.h"
#include <QImage>

QRPG::TileItem::TileItem(const TileType &type, QObject *parent) : GraphicsItem(parent), tileType(type)
{
    tileSize = 8;
    createImages();
}

//QRPG::TileItem::TileItem(const QRPGDao::QRPGTile &daoTile, QObject *parent)
//{

//}

QRPG::TileItem::~TileItem()
{
    delete voidImage;
    delete stoneImage;
    delete grassImage;
    delete waterImage;
}

void QRPG::TileItem::setTileType(const TileType &type)
{
    tileType = type;
}

void QRPG::TileItem::createImages()
{
    QRgb value;
    voidImage = new QImage(tileSize, tileSize, QImage::Format_RGB32);
    voidImage->fill(0x00000000);
    value = qRgb(0x66, 0x66, 0x66);
    for (int i=0; i < tileSize; i++) {
        for (int j=0; j < tileSize; j++) {
            if ((i % 4) / 2 == (j % 4) / 2) {
                voidImage->setPixel(i, j, value);
            }
        }
    }

    stoneImage = new QImage(tileSize, tileSize, QImage::Format_RGB32);
    stoneImage->fill(0xff888888);
    value = qRgb(0x66, 0x66, 0x66);
    stoneImage->setPixel(1, 1, value);
    stoneImage->setPixel(2, 1, value);
    stoneImage->setPixel(3, 2, value);
    stoneImage->setPixel(5, 3, value);
    stoneImage->setPixel(5, 4, value);
    stoneImage->setPixel(6, 5, value);

    grassImage = new QImage(tileSize, tileSize, QImage::Format_RGB32);
    grassImage->fill(0xff00ff00);
    value = qRgb(0x00, 0xaa, 0x00);
    grassImage->setPixel(1, 1, value);
    grassImage->setPixel(2, 1, value);
    grassImage->setPixel(3, 2, value);
    grassImage->setPixel(5, 3, value);
    grassImage->setPixel(5, 4, value);
    grassImage->setPixel(6, 5, value);

    waterImage = new QImage(tileSize, tileSize, QImage::Format_RGB32);
    waterImage->fill(0xff0000aa);
    value = qRgb(0x00, 0x00, 0xff);
    waterImage->setPixel(1, 2, value);
    waterImage->setPixel(2, 1, value);
    waterImage->setPixel(3, 1, value);
    waterImage->setPixel(4, 1, value);
    waterImage->setPixel(5, 2, value);
    waterImage->setPixel(6, 3, value);

    waterImage->setPixel(1, 5, value);
    waterImage->setPixel(2, 4, value);
    waterImage->setPixel(3, 4, value);
    waterImage->setPixel(4, 4, value);
    waterImage->setPixel(5, 5, value);
    waterImage->setPixel(6, 6, value);

    voidPixmap = QPixmap::fromImage(*voidImage);
    stonePixmap = QPixmap::fromImage(*stoneImage);
    grassPixmap = QPixmap::fromImage(*grassImage);
    waterPixmap = QPixmap::fromImage(*waterImage);
}

QRectF QRPG::TileItem::boundingRect() const
{
    return QRectF(0, 0, tileSize, tileSize);
}

const QPixmap *QRPG::TileItem::pixmap() const
{
    switch (tileType) {
    case STONE:
        return &stonePixmap;
        break;
    case GRASS:
        return &grassPixmap;
        break;
    case WATER:
        return &waterPixmap;
        break;
    default: // VOID
        return &voidPixmap;
        break;
    }
}

const QImage *QRPG::TileItem::image() const
{
    switch (tileType) {
    case STONE:
        return stoneImage;
        break;
    case GRASS:
        return grassImage;
        break;
    case WATER:
        return waterImage;
        break;
    default: // VOID
        return voidImage;
    }
}

void QRPG::TileItem::doTick()
{
}
