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
