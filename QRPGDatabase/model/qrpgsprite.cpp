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

