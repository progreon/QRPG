/*
This file is part of the QRPG project
Copyright (C) 2015  Marco Willems

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "qrpgscreen.h"
#include <QResizeEvent>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

QRPG::QRPGScreen::QRPGScreen(QWidget *parent) : QWidget(parent)
{
    _scale = 2.0;
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
//    setScreenPos(0, 0);
}

void QRPG::QRPGScreen::centerScreenOn(qreal x, qreal y)
{
    QRectF scaled = scaledRect();
    sceneRect = QRectF(x - scaled.width() / 2.0, y - scaled.height() / 2.0, scaled.width(), scaled.height());
}

QRectF QRPG::QRPGScreen::scaledRect() const
{
    return QRectF(0, 0, rect().width() / _scale, rect().height() / _scale);
}

QPointF QRPG::QRPGScreen::screenCenter() const
{
    return sceneRect.center();
}

QPointF QRPG::QRPGScreen::screenPos() const
{
    return sceneRect.topLeft();
}

//void QRPG::QRPGScreen::setScale(double scale)
//{
//    QPointF midPos = sceneRect.center();
//    this->_scale = scale;
//    currentBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
//    nextBuffer = new QPixmap(scaledRect().width(), scaledRect().height());
//    this->centerScreenOn(midPos.x(), midPos.y());
//    doRender();
//}

void QRPG::QRPGScreen::setScreenPos(qreal x, qreal y)
{
    sceneRect = QRectF(x, y, scaledRect().width(), scaledRect().height());
}

void QRPG::QRPGScreen::doRender()
{
    QMutexLocker locker(&renderMutex);
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
    if (scene != NULL) {
        if (currentBuffer != NULL) {
            QPainter painter(this);
            if (painter.isActive()) {
                painter.scale(_scale, _scale);
                painter.drawPixmap(0, 0, *currentBuffer);
            }
        }
    } else {
        QPainter painter(this);
        painter.fillRect(rect(), Qt::black);
    }
    _frames++;
}
