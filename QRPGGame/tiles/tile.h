#ifndef TILE_H
#define TILE_H

#include "../graphicsitem.h"
#include <QPixmap>
#include <QImage>

enum TileType {
    VOID,
    STONE,
    GRASS,
    WATER
};

class Tile : public GraphicsItem
{
public:
    Tile(const TileType &type, QObject *parent = 0);
    ~Tile();
    int getTileSize() const {return tileSize;}
    TileType getTileType() const {return tileType;}
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

    // GraphicsItem interface
public:
    virtual QRectF boundingRect() const;
    virtual const QPixmap *pixmap() const;
    virtual const QImage *image() const;

public slots:
    virtual void doTick();
};

#endif // TILE_H
