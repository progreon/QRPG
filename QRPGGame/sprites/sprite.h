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

#ifndef QRPG_SPRITE_H
#define QRPG_SPRITE_H

#include <QVector>
#include <QPixmap>
#include <QDebug>
#include "model/qrpgsprite.h"

namespace QRPG {
    class QRPGGame;
}

/**
 * This class is to make sure all the same sprites on the map change at the same time!
 */
namespace QRPG {

class Sprite
{
public:
    Sprite(QRPGGame *game, const QRPGDao::QRPGSprite *sprite);
    ~Sprite();

    void doTick();
    const QPixmap *pixmap() const;

private:
    QRPGGame *game;

//    const QRPGDao::QRPGSprite *sprite;
    QVector<const QPixmap *> spriteFrames;
    qreal fps;
    int spriteID;

    int _frameIndex;
    int _ticksPassed;
};

} // namespace QRPG

#endif // QRPG_SPRITE_H
