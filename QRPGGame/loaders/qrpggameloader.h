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
