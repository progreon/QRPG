#ifndef QRPG_QRPGSCREEN_H
#define QRPG_QRPGSCREEN_H

#include <QWidget>
#include <QMutex>
#include <QMutexLocker>
#include <QPixmap>
#include <QRectF>
#include <QRect>
#include <QPointF>
#include <QPoint>
#include "qrpgscene.h"

namespace QRPG {

class QRPGScreen : public QWidget
{
    Q_OBJECT
public:
    explicit QRPGScreen(QWidget *parent = 0);
    ~QRPGScreen();
    void centerScreenOn(qreal x, qreal y);
    double scale() const {return _scale;}
    QRectF scaledRect() const;
    QPointF screenCenter() const;
    QPointF screenPos() const;
//    void setScale(double scale);
    void setScreenPos(qreal x, qreal y);
    void setScene(QRPGScene *scene);

    int frames() const {return _frames;}
    void resetFrames() {_frames = 0;}

signals:

public slots:
    void doRender();

private:
    double _scale;
    QRPGScene *scene;
    QRectF sceneRect; // the part of the current scene that is shown
    QPixmap *currentBuffer;
    QPixmap *nextBuffer;

    int _frames;

    QMutex renderMutex;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *re);
    void paintEvent(QPaintEvent *);
};

}

#endif // QRPG_QRPGSCREEN_H
