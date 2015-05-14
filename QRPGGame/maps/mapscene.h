#ifndef QRPG_MAPSCENE_H
#define QRPG_MAPSCENE_H

#include <QVector>
#include "../tiles/tileitem.h"
#include "../qrpgscene.h"

namespace QRPG {

class MapScene : public QRPGScene
{
public:
    MapScene(int width = 20, int height = 20, QObject *parent = 0);
    ~MapScene();
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    TileItem *getTile(int x, int y) const;
    void setTileItem(int x, int y, TileItem *tile);

private:
    const int width, height;
    QVector<QVector<TileItem *> > tiles;
    int ticksPassed;

    // Scene interface
public slots:
    void doTick();
};

}

#endif // QRPG_MAPSCENE_H
