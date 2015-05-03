#ifndef QRGP_SPRITE_H
#define QRGP_SPRITE_H

#include <QVector>
#include <QPixmap>

namespace QRGP {

class Sprite
{
public:
    Sprite(QVector<QPixmap *> spriteFrames, qreal fps = 0);
    ~Sprite();

private:
    QVector<QPixmap *> spriteFrames;
    qreal fps;
};

} // namespace QRGP

#endif // QRGP_SPRITE_H
