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

#ifndef QRPG_QRPGMAPLOADER_H
#define QRPG_QRPGMAPLOADER_H

#include <QObject>
#include <QMap>
#include <QPixmap>
#include "model/qrpgmap.h"
#include "../maps/mapscene.h"

namespace QRPG {

class QRPGGame;

class QRPGMapLoader : public QObject
{
    Q_OBJECT
public:
    explicit QRPGMapLoader(QRPGGame *game, QObject *parent = 0);
    ~QRPGMapLoader();
    MapScene *newMap(QRPGDao::QRPGMap *map);
//    MapScene *newExampleMap();

signals:

public slots:

private:
    QRPGGame *_game;
};

} // namespace QRPG

#endif // QRPG_QRPGMAPLOADER_H
