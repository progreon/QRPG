#include "qrpgmaploader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include <model/qrpgtile.h>
#include "tiles/tileitem.h"
#include "../qrpggame.h"

namespace QRPG {

QRPGMapLoader::QRPGMapLoader(QRPGGame *game, QObject *parent)
    : QObject(parent)
    , _game(game)
{

}

QRPGMapLoader::~QRPGMapLoader()
{

}

MapScene *QRPGMapLoader::newMap(QRPGDao::QRPGMap *map)
{
    MapScene *mapScene = new MapScene(map->width(), map->height());
    // TODO
    for (int l=0; l<3; l++) {
        for (int x=0; x<map->width(); x++) {
            for (int y=0; y<map->height(); y++) {
                const QRPGDao::QRPGTile *daoTile = map->tile(l, x, y);
                if (daoTile != NULL) {
                    TileItem *tile = new TileItem(_game->sprite(daoTile->sprite()->ID()));
                    mapScene->setTileItem(x, y, tile);
                }
            }
        }
    }
    return mapScene;
}

} // namespace QRPG

