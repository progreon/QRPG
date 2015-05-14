#ifndef QRPGDAO_SPRITE_H
#define QRPGDAO_SPRITE_H

#include <QVector>
#include <QPixmap>

namespace QRPGDao {

class QRPGSprite
{
public:
    QRPGSprite(int ID, qreal fps = 0);
    ~QRPGSprite();
    void addSpriteFrame(const QPixmap &spriteFrame);
    qreal fps() const {return _fps;}
    int ID() const {return _ID;}
    bool removeSpriteFrame(int index);
    void setFps(qreal fps);
    QVector<const QPixmap *> spriteFrames() const;
private:
    const int _ID;
    QVector<QPixmap> _spriteFrames;
    qreal _fps;
};

} // namespace QRPGDao

#endif // QRPGDAO_SPRITE_H
