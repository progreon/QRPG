#ifndef QRPGDAO_QRPGTILE_H
#define QRPGDAO_QRPGTILE_H

#include "qrpgsprite.h"

namespace QRPGDao {

class QRPGTile
{
public:
    QRPGTile(int ID, const QString &name, QRPGSprite *sprite);
    ~QRPGTile();
    int ID() const {return _ID;}
    QString name() const {return _name;}
    QRPGSprite *sprite() const {return _sprite;}

private:
    const int _ID;
    const QString _name;
    QRPGSprite *_sprite;
};

} // namespace QRPGDao

#endif // QRPGDAO_QRPGTILE_H
