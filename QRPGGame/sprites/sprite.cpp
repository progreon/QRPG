#include "sprites/sprite.h"

namespace QRGP {

Sprite::Sprite(QVector<QPixmap *> spriteFrames, qreal fps)
    : spriteFrames(spriteFrames)
    , fps(fps)
{

}

Sprite::~Sprite()
{

}

} // namespace QRGP

