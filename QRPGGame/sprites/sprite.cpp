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

#include "sprites/sprite.h"
#include "../qrpggame.h"

namespace QRPG {

Sprite::Sprite(QRPGGame *game, const QRPGDao::QRPGSprite *sprite)
{
    this->game = game;
    spriteFrames = sprite->spriteFrames();
    fps = sprite->fps();
    spriteID = sprite->ID();

    _frameIndex = 0;
    _ticksPassed = 0;
}

Sprite::~Sprite()
{

}

void Sprite::doTick()
{
    _ticksPassed++;
    if (_ticksPassed >= (game->tps() / fps)) {
        _ticksPassed = 0;
        if (_frameIndex < spriteFrames.size() - 1) {
            _frameIndex++;
        } else {
            _frameIndex = 0;
        }
    }
}

const QPixmap *Sprite::pixmap() const
{
    return spriteFrames.value(_frameIndex);
}

} // namespace QRGP

