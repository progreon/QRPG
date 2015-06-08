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

#ifndef QRPG_QRPGGAMELOADER_H
#define QRPG_QRPGGAMELOADER_H

#include <QObject>
#include "qrpgdatabase.h"

namespace QRPG {

class QRPGGameLoader : public QObject
{
    Q_OBJECT
public:
//    explicit QRPGGameLoader(QRPGDao::QRPGDatabase *dao, QObject *parent = 0);
    explicit QRPGGameLoader(QObject *parent = 0);
    ~QRPGGameLoader();

signals:

public slots:

private:
//    QRPGDao::QRPGDatabase *dao;
};

} // namespace QRPG

#endif // QRPG_QRPGGAMELOADER_H
