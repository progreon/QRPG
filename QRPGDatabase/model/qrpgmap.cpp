#include "qrpgmap.h"
#include "qrpgproject.h"

namespace QRPGDao {

QRPGMap::QRPGMap(QRPGProject *project, int ID, QString name, int width, int height)
    : _project(project)
    , _ID(ID)
    , _name(name)
    , _width(width)
    , _height(height)
{
    tiles.resize(3);
    for (int l = 0; l < 3; l++) { // loop all layers
        tiles[l].resize(width);
        for (int x=0; x<width; x++) { // loop the width
            tiles[l][x].resize(height);
            for (int y=0; y<height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    setSpawn(0, 0);
}

QRPGMap::~QRPGMap()
{
    
}

void QRPGMap::setHeight(int height)
{
    for (int l=0; l<3; l++) { // loop all layers
        for (int x=0; x<_width; x++) { // loop the width
            tiles[l][x].resize(height);
            for (int y=_height; y<height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    _height = height;
}

bool QRPGMap::setSpawn(int x, int y)
{
    if (x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    } else {
        _spawn = QPoint(x, y);
        return true;
    }
}

bool QRPGMap::setTile(int layer, int x, int y, QRPGTile *tile)
{
    if (layer < 0 || layer >= 3 || x < 0 || x >= _width || y < 0 || y >= _height) {
        return false;
    } else {
        tiles[layer][x][y] = tile;
        return true;
    }
}

void QRPGMap::setWidth(int width)
{
    for (int l = 0; l < 3; l++) { // loop all layers
        tiles[l].resize(width);
        for (int x=_width; x<width; x++) { // loop the width
            tiles[l][x].resize(_height);
            for (int y=0; y<_height; y++) { // loop the height
                tiles[l][x][y] = NULL; // be sure all is NULL
            }
        }
    }
    _width = width;
}

} // namespace QRPGDao

