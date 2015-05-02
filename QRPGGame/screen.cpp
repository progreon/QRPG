#include "screen.h"
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

Screen::Screen(QWidget *parent) : QWidget(parent)
{
    scale = 3.0;
    currentBuffer = 0;
    nextBuffer = 0;
    setScene(0);
    //    scene = 0;
}

Screen::~Screen()
{
    delete currentBuffer;
    delete nextBuffer;
}

void Screen::setScene(Scene *scene)
{
    this->scene = scene;
    //    sceneRect = QRectF(0, 0, rect().width(), rect().height());
    if (currentBuffer != NULL) delete currentBuffer;
    if (nextBuffer != NULL) delete nextBuffer;
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    setScreenPos(0, 0);
}

void Screen::centerScreenOn(qreal x, qreal y)
{
    sceneRect = QRectF(x - scaledRect().width() / 2.0, y - scaledRect().height() / 2.0, scaledRect().width(), scaledRect().height());
}

QRect Screen::scaledRect() const
{
    return QRect(0, 0, rect().width() / scale, rect().height() / scale);
}

QPointF Screen::screenCenter() const
{
    return sceneRect.center();
}

QPointF Screen::screenPos() const
{
    return sceneRect.topLeft();
}

void Screen::setScreenPos(qreal x, qreal y)
{
    sceneRect = QRectF(x, y, scaledRect().width(), scaledRect().height());
}

void Screen::doRender()
{
    if (scene != NULL) {
        scene->render(nextBuffer, screenPos());
    }
    std::swap(currentBuffer, nextBuffer);
    update();
    //    repaint();
}

void Screen::resizeEvent(QResizeEvent *re)
{
    QPointF midPos = sceneRect.center();
    QWidget::resizeEvent(re);
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    centerScreenOn(midPos.x(), midPos.y());
    doRender();
}

void Screen::paintEvent(QPaintEvent *)
{
    //    qDebug() << "Screen::paintEvent(), width: " << rect().width() << ", height: " << rect().height();
    if (scene != NULL) {
        //        QRectF drawRect = currentBuffer->rect().intersected(scene->boundingRect());
        if (currentBuffer != NULL) {
            QPainter painter(this);
            if (painter.isActive()) {
                painter.scale(scale, scale);
                painter.drawPixmap(0, 0, *currentBuffer);
            }
        }
    } else {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::black);
    }
    _frames++;
}
