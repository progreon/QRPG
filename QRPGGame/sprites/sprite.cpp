#include "sprites/sprite.h"
#include "../qrpggame.h"

namespace QRPG {

//Sprite::Sprite(QVector<const QPixmap *> spriteFrames, qreal fps)
//    : spriteFrames(spriteFrames)
//    , fps(fps)
//{

//}

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

} // namespace QRGP

