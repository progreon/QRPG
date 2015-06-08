/*
This file is part of the QRPG project
Copyright (C) 2015  Marco Willems

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
