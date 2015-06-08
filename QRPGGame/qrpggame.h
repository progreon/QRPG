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

#ifndef QRPG_QRPGGAME_H
#define QRPG_QRPGGAME_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMutexLocker>
#include <QMap>
#include "model/qrpgproject.h"
#include "qrpgscreen.h"
#include "qrpgscene.h"
#include "loaders/qrpgmaploader.h"
#include "maps/mapscene.h"
#include "sprites/sprite.h"

namespace QRPG {

class QRPGGame : public QObject
{
    Q_OBJECT
public:
    explicit QRPGGame(QRPGScreen *screen, const QRPGDao::QRPGProject *project);
    ~QRPGGame();
    bool isRunning() const {return running;}
    void keyPressed(int key);
    void keyReleased(int key);
    void openMap(int mapID);
    void setupThread(QThread *gameThread);
    Sprite *sprite(int ID) const;
    const QMap<int, Sprite *> sprites() const {return usedSprites;}
    void stop();
    qreal tps() const {return _tps;}

signals:
    void render();

public slots:
    void start();

private:
    qreal _tps;

    QRPGScreen *screen;
    QMap<int, bool> input;
    QThread *gameThread;
    QMutex inputMutex;
    QMutex startMutex;

    QMap<int, Sprite *> usedSprites;
    void loadSprites(const QRPGDao::QRPGProject *project);
    MapScene *map;
    void handleInput();

    volatile bool running;
    volatile bool looping;
    void run();
    void tick();

    const QRPGDao::QRPGProject *currProject;
    QRPGMapLoader mapLoader;
};

}

#endif // QRPG_QRPGGAME_H
