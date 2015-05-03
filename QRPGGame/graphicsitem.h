#ifndef QRPG_GRAPHICSITEM_H
#define QRPG_GRAPHICSITEM_H

#include <QObject>
#include <QPixmap>
#include <QImage>
#include <QRectF>
#include <QPointF>

namespace QRPG {

class GraphicsItem : public QObject
{
    Q_OBJECT
public:
    explicit GraphicsItem(QObject *parent = 0);
    ~GraphicsItem();
    virtual QRectF boundingRect() const = 0;
    virtual QPointF pos() const;
    virtual void moveBy(qreal dx, qreal dy);
    virtual const QPixmap *pixmap() const = 0;
    virtual const QImage *image() const = 0;
    virtual QRectF sceneBoundingRect() const;
    virtual void setPos(qreal x, qreal y);

signals:

public slots:
    virtual void doTick() = 0;

private:
    QPointF _pos;

};

}

#endif // QRPG_GRAPHICSITEM_H
