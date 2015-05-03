#ifndef SCREEN_H
#define SCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QRectF>
#include <QRect>
#include <QPointF>
#include <QPoint>
#include "qrpgscene.h"

namespace QRPG {

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = 0);
    ~Screen();
    void centerScreenOn(qreal x, qreal y);
    QRect scaledRect() const;
    QPointF screenCenter() const;
    QPointF screenPos() const;
    void setScreenPos(qreal x, qreal y);
    void setScene(Scene *scene);

    int frames() const {return _frames;}
    void resetFrames() {_frames = 0;}

signals:

public slots:
    void doRender();

private:
    double scale;
    Scene *scene;
    QRectF sceneRect; // the part of the current scene that is shown
    QPixmap *currentBuffer;
    QPixmap *nextBuffer;

    int _frames;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *re);
    void paintEvent(QPaintEvent *);
};

}

#endif // SCREEN_H
