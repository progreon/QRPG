#ifndef QRPG_MAPSCENE_H
#define QRPG_MAPSCENE_H

#include <QVector>
#include "../tiles/tileitem.h"
#include "../qrpgscene.h"

namespace QRPG {

class Map : public Scene
{
public:
    Map(int width = 20, int height = 20, QObject *parent = 0);
    ~Map();
    int getWidth() const {return width;}
    int getHeight() const {return height;}
    Tile *getTile(int x, int y) const;

private:
    const int width, height;
    QVector<QVector<Tile *> > tiles;
    int ticksPassed;

    // Scene interface
public slots:
    void doTick();
};

}

#endif // QRPG_MAPSCENE_H
