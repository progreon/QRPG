#ifndef MAP_H
#define MAP_H

#include <QVector>
#include "../tiles/tile.h"
#include "../scene.h"

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

#endif // MAP_H
