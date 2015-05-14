#include "qrpgmaploader.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QVector>
#include "tiles/tileitem.h"

namespace QRPG {

QRPGMapLoader::QRPGMapLoader(QRPGDao::QRPGDatabase *dao, QObject *parent)
    : QObject(parent)
    , dao(dao)
{

}

QRPGMapLoader::~QRPGMapLoader()
{

}

MapScene *QRPGMapLoader::newMap(QRPGDao::QRPGMap *map)
{
    MapScene *mapScene = new MapScene(map->width(), map->height());
    // TODO
    // Where to load the sprites??
}

MapScene *QRPGMapLoader::newExampleMap()
{
    int maxX = 0;
    int maxY = 0;
    loadSprites();

    MapScene *mapScene = new MapScene(10, 10);

    QFile mapsample(":qrpg/files/mapsample");
    if (mapsample.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&mapsample);
        while (!in.atEnd()) {
            QString line = in.readLine();
            line = line.trimmed();
            if (!line.isEmpty() && !line.startsWith('#')) {
                QStringList lineargs = line.split(";");
                if (lineargs.length() == 4) {
                    int layer = lineargs.at(0).toInt();
                    int x = lineargs.at(1).toInt();
                    int y = lineargs.at(2).toInt();
                    if (x > maxX) maxX = x;
                    if (y > maxY) maxY = y;
                    int tileID = lineargs.at(3).toInt();
                    qDebug() << "layer " << layer << ": (" << x << "," << y << ") = " << tileID;
                    TileItem *tile = new TileItem(CURRENT);
                    tile->setSprite(sprites.value(tileID));
                    mapScene->setTileItem(x, y, tile);
                }
            }
        }
        mapsample.close();
    }
    return mapScene;
}

void QRPGMapLoader::loadSprites()
{
    QFile tilessample(":qrpg/files/tilessample");
    if (tilessample.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&tilessample);
        while (!in.atEnd()) {
            QString line = in.readLine();
            line = line.trimmed();
            if (!line.isEmpty() && !line.startsWith('#')) {
                QStringList lineargs = line.split(";");
                if (lineargs.length() == 5) {
                    int id = lineargs.at(0).toInt();
                    QString name = lineargs.at(1);
                    QString file = lineargs.at(2);
                    int x = lineargs.at(3).toInt();
                    int y = lineargs.at(4).toInt();
                    qDebug() << id << ": " << name << "(" << file << ": (" << x << "," << y << "))";
                    QPixmap spritesheet(QString(":qrpg/files/").append(file));
                    QPixmap sprite = spritesheet.copy(x, y, 8, 8);
                    sprites.insert(id, sprite);
                    qDebug() << sprite;
                }
            }
        }
        tilessample.close();
    }
}

} // namespace QRPG

