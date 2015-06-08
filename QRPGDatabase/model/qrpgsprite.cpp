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

#include "qrpgsprite.h"

namespace QRPGDao {

QRPGSprite::QRPGSprite(int ID, qreal fps)
    : _ID(ID)
    , _fps(fps)
{

}

QRPGSprite::~QRPGSprite()
{

}

void QRPGSprite::addSpriteFrame(const QPixmap &spriteFrame)
{
    _spriteFrames.append(spriteFrame);
}

bool QRPGSprite::removeSpriteFrame(int index)
{
    if (index < 0 || index >= _spriteFrames.length()) {
        return false;
    } else {
        _spriteFrames.remove(index);
        return true;
    }
}

void QRPGSprite::setFps(qreal fps)
{
    this->_fps = fps;
}

QVector<const QPixmap *> QRPGSprite::spriteFrames() const
{
    QVector<const QPixmap *> frames;
    for (int i=0; i<_spriteFrames.length(); i++) {
        frames.append(&(_spriteFrames.at(i)));
    }
    return frames;
}

} // namespace QRPGDao

