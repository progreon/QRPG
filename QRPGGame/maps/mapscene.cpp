#include "mapscene.h"
#include <QDebug>

QRPG::MapScene::MapScene(int width, int height, QObject *parent) : QRPGScene(parent), width(width), height(height)
{
    tiles.resize(width);
    for (int i = 0; i < width; i++) {
        tiles[i].resize(height);
    }
    ticksPassed = 0;
}

QRPG::MapScene::~MapScene()
{
    for (int i = 0; i < tiles.length(); i++) {
        for (int j = 0; j < tiles[i].length(); j++) {
            delete tiles[i][j];
        }
    }
}

QRPG::TileItem *QRPG::MapScene::getTile(int x, int y) const
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return tiles[x][y];
    } else {
        return NULL;
    }
}

void QRPG::MapScene::setTileItem(int x, int y, QRPG::TileItem *tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height) {
//        deleteGraphicsItem(tiles[x][y]);
//        delete tiles[x][y];
        tile->setPos(x * tile->tileSize(), y * tile->tileSize());
        tiles[x][y] = tile;
        addGraphicsItem(tile);
    }
}

void QRPG::MapScene::doTick()
{

}
