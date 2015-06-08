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

#ifndef QRPGDAO_SPRITE_H
#define QRPGDAO_SPRITE_H

#include <QVector>
#include <QPixmap>

namespace QRPGDao {

class QRPGSprite
{
public:
    QRPGSprite(int ID, qreal fps = 0);
    ~QRPGSprite();
    void addSpriteFrame(const QPixmap &spriteFrame);
    qreal fps() const {return _fps;}
    int ID() const {return _ID;}
    bool removeSpriteFrame(int index);
    void setFps(qreal fps);
    QVector<const QPixmap *> spriteFrames() const;
private:
    const int _ID;
    QVector<QPixmap> _spriteFrames;
    qreal _fps;
};

} // namespace QRPGDao

#endif // QRPGDAO_SPRITE_H
