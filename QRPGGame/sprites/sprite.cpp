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
//    for (int i=0; i<spriteFrames.size(); i++) {
//        spriteFramesCopy.append(QPixmap(*(spriteFrames.value(i))));
//    }
    fps = sprite->fps();
    spriteID = sprite->ID();

//    qDebug() << "sprite" << spriteID << "with" << spriteFrames.size() << "frames";

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
//    qDebug() << "getting sprite with index" << _frameIndex;
    return spriteFrames.value(_frameIndex);
//    return &(spriteFramesCopy[_frameIndex]);
}

} // namespace QRGP

