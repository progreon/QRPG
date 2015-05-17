#ifndef QRPG_TILEITEM_H
#define QRPG_TILEITEM_H

#include <QPixmap>
#include <QImage>
#include "../graphicsitem.h"
#include "../sprites/sprite.h"

namespace QRPG {

class TileItem : public GraphicsItem
{
public:
    TileItem(Sprite *sprite, QObject *parent = 0);
    ~TileItem();
    int getTileSize() const;

private:
    int tileSize;

    Sprite *sprite;
//    Sprite spriteCopy;

    // GraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual const QPixmap *pixmap() const;
//    virtual const QImage *image() const;

public slots:
    virtual void doTick();
};

}

#endif // QRPG_TILEITEM_H
