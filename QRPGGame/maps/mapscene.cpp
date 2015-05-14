#include "mapscene.h"

QRPG::MapScene::MapScene(int width, int height, QObject *parent) : QRPGScene(parent), width(width), height(height)
{
    const int numColors = 4;
    tiles.resize(width);
    for (int i = 0; i < width; i++) {
        tiles[i].resize(height);
        for (int j = 0; j < height; j++) {
//            tiles[i][j] = new TileItem(TileType(qrand() % numColors));
//            tiles[i][j]->setPos(i * 8, j * 8);
//            addGraphicsItem(tiles[i][j]);
        }
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
        tile->setPos(x * 8, y * 8);
        tiles[x][y] = tile;
        addGraphicsItem(tile);
    }
}

void QRPG::MapScene::doTick()
{
    ticksPassed++;
    if (ticksPassed >= 2) {
        //        const int numColors = 4;
        for (int i = 0; i < getWidth(); i++) {
            TileType firstType = getTile(i, 0)->getTileType();
            int j;
            for (j = 1; j < getHeight(); j++) {
                getTile(i, j-1)->setTileType(getTile(i, j)->getTileType());
                //                getTile(i, j)->setTileType(TileType(qrand() % numColors));
            }
            getTile(i, j-1)->setTileType(firstType);
        }
        ticksPassed -= 2;
    }

}
