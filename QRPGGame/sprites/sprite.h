#ifndef QRGP_SPRITE_H
#define QRGP_SPRITE_H

#include <QVector>
#include <QPixmap>
#include "model/qrpgsprite.h"
#include "../qrpggame.h"

/**
 * This class is to make sure all the same sprites on the map change at the same time!
 */
namespace QRGP {

class Sprite
{
public:
//    Sprite(QVector<const QPixmap *> spriteFrames, qreal fps = 0);
    Sprite(QRPG::QRPGGame *game, const QRPGDao::QRPGSprite *sprite);
    ~Sprite();

    void doTick();
    const QPixmap *pixmap() const {return spriteFrames.value(_frameIndex);}

private:
    QRPG::QRPGGame *game;

    const QRPGDao::QRPGSprite *sprite;
    QVector<const QPixmap *> spriteFrames;
    qreal fps;
    int spriteID;

    int _frameIndex;
    int _ticksPassed;
};

} // namespace QRGP

#endif // QRGP_SPRITE_H
