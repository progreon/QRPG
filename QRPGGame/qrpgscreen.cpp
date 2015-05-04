#include "qrpgscreen.h"
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

QRPG::QRPGScreen::QRPGScreen(QWidget *parent) : QWidget(parent)
{
    scale = 3.0;
    currentBuffer = 0;
    nextBuffer = 0;
    setScene(0);
    //    scene = 0;
}

QRPG::QRPGScreen::~QRPGScreen()
{
    delete currentBuffer;
    delete nextBuffer;
}

void QRPG::QRPGScreen::setScene(QRPGScene *scene)
{
    this->scene = scene;
    //    sceneRect = QRectF(0, 0, rect().width(), rect().height());
    if (currentBuffer != NULL) delete currentBuffer;
    if (nextBuffer != NULL) delete nextBuffer;
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    setScreenPos(0, 0);
}

void QRPG::QRPGScreen::centerScreenOn(qreal x, qreal y)
{
    sceneRect = QRectF(x - scaledRect().width() / 2.0, y - scaledRect().height() / 2.0, scaledRect().width(), scaledRect().height());
}

QRect QRPG::QRPGScreen::scaledRect() const
{
    return QRect(0, 0, rect().width() / scale, rect().height() / scale);
}

QPointF QRPG::QRPGScreen::screenCenter() const
{
    return sceneRect.center();
}

QPointF QRPG::QRPGScreen::screenPos() const
{
    return sceneRect.topLeft();
}

void QRPG::QRPGScreen::setScreenPos(qreal x, qreal y)
{
    sceneRect = QRectF(x, y, scaledRect().width(), scaledRect().height());
}

void QRPG::QRPGScreen::doRender()
{
    if (scene != NULL) {
        scene->render(nextBuffer, screenPos());
    }
    std::swap(currentBuffer, nextBuffer);
    update();
}

void QRPG::QRPGScreen::resizeEvent(QResizeEvent *re)
{
    QPointF midPos = sceneRect.center();
    QWidget::resizeEvent(re);
    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
    centerScreenOn(midPos.x(), midPos.y());
    doRender();
}

void QRPG::QRPGScreen::paintEvent(QPaintEvent *)
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
