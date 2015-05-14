#ifndef QRPG_TILEITEM_H
#define QRPG_TILEITEM_H

#include "../graphicsitem.h"
#include <QPixmap>
#include <QImage>

namespace QRPG {

enum TileType {
    VOID,
    STONE,
    GRASS,
    WATER,
    CURRENT
};

class TileItem : public GraphicsItem
{
public:
    TileItem(const TileType &type, QObject *parent = 0);
//    TileItem(const QRPGDao::QRPGTile &daoTile, QObject *parent = 0); // TODO
    ~TileItem();
    int getTileSize() const {return tileSize;}
    TileType getTileType() const {return tileType;}
    void setSprite(QPixmap sprite) {currentSprite = sprite;}
    void setTileType(const TileType &type);

private:
    TileType tileType;

    void createImages();
    int tileSize;
    QImage *voidImage;
    QImage *stoneImage;
    QImage *grassImage;
    QImage *waterImage;
    QPixmap voidPixmap;
    QPixmap stonePixmap;
    QPixmap grassPixmap;
    QPixmap waterPixmap;

    QPixmap currentSprite;

    // GraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual const QPixmap *pixmap() const;
    virtual const QImage *image() const;

public slots:
    virtual void doTick();
};

}

#endif // QRPG_TILEITEM_H
