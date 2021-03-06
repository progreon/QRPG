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

#include "qrpggame.h"

#include <QDebug>
#include <QDateTime>
#include "model/qrpgsprite.h"

QRPG::QRPGGame::QRPGGame(QRPGScreen *screen, const QRPGDao::QRPGProject *project)
    : mapLoader(this)
{
    this->_tps = 60.0;
    this->screen = screen;
    map = NULL;
    currProject = NULL;
    running = false;
    connect(this, SIGNAL(render()), screen, SLOT(doRender()));
    qDebug() << "opening project ...";
    if (project != NULL) {
        currProject = project;
        loadSprites(currProject);
//        openMap(0);
    }
    qDebug() << "done opening project";
}

QRPG::QRPGGame::~QRPGGame()
{
    this->stop();
    delete map;
    foreach (Sprite *sprite, usedSprites) {
        delete sprite;
    }
}

void QRPG::QRPGGame::keyPressed(int key)
{
    inputMutex.lock();
    input.insert(key, true);
    inputMutex.unlock();
}

void QRPG::QRPGGame::keyReleased(int key)
{
    inputMutex.lock();
    input.insert(key, false);
    inputMutex.unlock();
}

void QRPG::QRPGGame::openMap(int mapID)
{
    if (currProject != NULL && screen != NULL) {
        MapScene *newMapScene = mapLoader.newMap(currProject->maps().value(mapID));
        MapScene *tempMap = map;
        map = newMapScene;
        if (tempMap != NULL) delete tempMap;
        screen->setScene(map);
        screen->centerScreenOn(0, 0);
    }
}

void QRPG::QRPGGame::setupThread(QThread *gameThread)
{
    this->gameThread = gameThread;
    connect(gameThread, SIGNAL(started()), this, SLOT(start()));
}

QRPG::Sprite *QRPG::QRPGGame::sprite(int ID) const
{
    return usedSprites.value(ID);
}

void QRPG::QRPGGame::handleInput()
{
    QPointF pos = screen->screenPos();
    if (input[Qt::Key_Left] | input[Qt::Key_Q]) {
        pos.setX(pos.x() - 1.0);
    }
    if (input[Qt::Key_Right] | input[Qt::Key_D]) {
        pos.setX(pos.x() + 1.0);
    }
    if (input[Qt::Key_Up] | input[Qt::Key_Z]) {
        pos.setY(pos.y() - 1.0);
    }
    if (input[Qt::Key_Down] | input[Qt::Key_S]) {
        pos.setY(pos.y() + 1.0);
    }
//    if (input[Qt::Key_Minus]) {
//        screen->setScale(screen->scale() - 0.01);
//    }
//    if (input[Qt::Key_Plus]) {
//        screen->setScale(screen->scale() + 0.01);
//    }
    screen->setScreenPos(pos.x(), pos.y());
//    screen->centerScreenOn(pos.x(), pos.y());
}

void QRPG::QRPGGame::start()
{
    if (currProject != NULL) {
        qDebug() << "Starting...";
        looping = true;
        run();
    } else {
        qDebug() << "Did not start, current project = NULL!";
    }
}

void QRPG::QRPGGame::loadSprites(const QRPGDao::QRPGProject *project)
{
    foreach (Sprite *sprite, usedSprites) {
        delete sprite;
    }
    foreach (QRPGDao::QRPGSprite *qrpgSprite, project->sprites().values()) {
        usedSprites.insert(qrpgSprite->ID(), new Sprite(this, qrpgSprite));
    }
}

void QRPG::QRPGGame::stop()
{
    if (isRunning()) {
        qDebug() << "stopping...";
        looping = false;
        while (isRunning()) {}
        gameThread->exit();
        qDebug() << "stopped";
    }
}

void QRPG::QRPGGame::run()
{
    running = true;

    double msPerTick = 1000.0/_tps;
    int ticks = 0;
    int frames = 0;
    screen->resetFrames();
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    qint64 last = QDateTime::currentMSecsSinceEpoch();
    float delta = 0.0;

    while (looping) {
        qint64 now = QDateTime::currentMSecsSinceEpoch();
        qint64 deltams = now - last;
        last = now;
        delta += deltams / msPerTick;
        bool shouldRender = true;
        while (delta >= 1) {
            ticks++;
            tick();
            delta -= 1;
        }
        gameThread->usleep(3000);
        if (shouldRender) {
            frames++;
            emit render();
//            screen->doRender();
        }
        if (QDateTime::currentMSecsSinceEpoch() - start >= 1000) {
            start += 1000;
            qDebug() << ticks << " ticks, " << frames << " renders, " << screen->frames() << " real frames";
            ticks = 0;
            frames = 0;
            screen->resetFrames();
        }

    }
    running = false;
}

void QRPG::QRPGGame::tick()
{
    foreach (Sprite *sprite, usedSprites.values()) {
        sprite->doTick();
    }
//    map.doTick();
    handleInput();
}

