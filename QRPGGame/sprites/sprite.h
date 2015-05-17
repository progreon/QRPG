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
//    Sprite(QVector<const QPixmap *> spriteFrames, qreal fps = 0);
    Sprite(QRPGGame *game, const QRPGDao::QRPGSprite *sprite);
    ~Sprite();

    void doTick();
    const QPixmap *pixmap() const;

private:
    QRPGGame *game;

//    const QRPGDao::QRPGSprite *sprite;
    QVector<const QPixmap *> spriteFrames;
//    QVector<QPixmap> spriteFramesCopy;
    qreal fps;
    int spriteID;

    int _frameIndex;
    int _ticksPassed;
};

} // namespace QRPG

#endif // QRPG_SPRITE_H
