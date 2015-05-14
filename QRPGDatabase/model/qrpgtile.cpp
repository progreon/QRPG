#include "qrpgtile.h"
#include <QDebug>

namespace QRPGDao {

QRPGTile::QRPGTile(int ID, const QString &name, QRPGSprite *sprite)
    : _ID(ID)
    , _name(name)
    , _sprite(sprite)
{

}

QRPGTile::~QRPGTile()
{

}

} // namespace QRPGDao

