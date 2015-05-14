#ifndef QRPGDAO_QRPGMAP_H
#define QRPGDAO_QRPGMAP_H

#include "qrpgtile.h"
#include <QVector>
#include <QPoint>

namespace QRPGDao {

class QRPGProject;

class QRPGMap
{
public:
    QRPGMap(QRPGProject *project, int ID, QString name, int width = 20, int height = 20);
    ~QRPGMap();
    int height() const {return _height;}
    int ID() const {return _ID;}
    QString name() const {return _name;}
    const QRPGProject *project() const {return _project;}
    void setHeight(int height);
    bool setSpawn(int x, int y);
    bool setTile(int layer, int x, int y, QRPGTile *tile);
    void setWidth(int width);
    QPoint spawn() const {return _spawn;}
    const QRPGTile *tile(int layer, int x, int y);
    int width() const {return _width;}

private:
    const QRPGProject *_project;
    const int _ID;
    QString _name;
    int _width, _height;
    // different tiles on 3 layers (base, buildings, extra)
    // the original tiles are kept in the project object
    QVector<QVector<QVector<QRPGTile *> > > tiles; // tiles[layer][x][y]
    // player spawn
    QPoint _spawn;
    // NPCs
    // map areas
    // events
    // ...


};

} // namespace QRPGDao

#endif // QRPGDAO_QRPGMAP_H
