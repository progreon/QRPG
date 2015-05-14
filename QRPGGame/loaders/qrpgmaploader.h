#ifndef QRPG_QRPGMAPLOADER_H
#define QRPG_QRPGMAPLOADER_H

#include <QObject>
#include <QMap>
#include <QPixmap>
#include "model/qrpgmap.h"
#include "qrpgdatabase.h"
#include "maps/mapscene.h"

namespace QRPG {

class QRPGMapLoader : public QObject
{
    Q_OBJECT
public:
    explicit QRPGMapLoader(QRPGDao::QRPGDatabase *dao = 0, QObject *parent = 0);
    ~QRPGMapLoader();
    MapScene *newMap(QRPGDao::QRPGMap *map);
    MapScene *newExampleMap();

signals:

public slots:

private:
    QRPGDao::QRPGDatabase *dao;
    QMap<int, QPixmap> sprites;
    void loadSprites();
};

} // namespace QRPG

#endif // QRPG_QRPGMAPLOADER_H
