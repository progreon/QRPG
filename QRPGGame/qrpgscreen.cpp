#include "qrpgscreen.h"
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

QRPG::Screen::Screen(QWidget *parent) : QWidget(parent)
{
    scale = 3.0;
    currentBuffer = 0;
    nextBuffer = 0;
    setScene(0);
    //    scene = 0;
}

QRPG::Screen::~Screen()
{
    delete currentBuffer;
    delete nextBuffer;
}

void QRPG::Screen::setScene(Scene *scene)
{
    this->scene = scene;
    //    sceneRect = QRectF(0, 0, rect().width(), rect().height());
    if (currentBuffer != NULL) delete currentBuffer;
    if (nextBuffer != NULL) delete nextBuffer;
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    setScreenPos(0, 0);
}

void QRPG::Screen::centerScreenOn(qreal x, qreal y)
{
    sceneRect = QRectF(x - scaledRect().width() / 2.0, y - scaledRect().height() / 2.0, scaledRect().width(), scaledRect().height());
}

QRect QRPG::Screen::scaledRect() const
{
    return QRect(0, 0, rect().width() / scale, rect().height() / scale);
}

QPointF QRPG::Screen::screenCenter() const
{
    return sceneRect.center();
}

QPointF QRPG::Screen::screenPos() const
{
    return sceneRect.topLeft();
}

void QRPG::Screen::setScreenPos(qreal x, qreal y)
{
    sceneRect = QRectF(x, y, scaledRect().width(), scaledRect().height());
}

void QRPG::Screen::doRender()
{
    if (scene != NULL) {
        scene->render(nextBuffer, screenPos());
    }
    std::swap(currentBuffer, nextBuffer);
    update();
    //    repaint();
}

void QRPG::Screen::resizeEvent(QResizeEvent *re)
{
    QPointF midPos = sceneRect.center();
    QWidget::resizeEvent(re);
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    centerScreenOn(midPos.x(), midPos.y());
    doRender();
}

void QRPG::Screen::paintEvent(QPaintEvent *)
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
