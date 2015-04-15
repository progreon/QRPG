#ifndef QRPGDAO_IMPL_QRPGDUMMYDAO_H
#define QRPGDAO_IMPL_QRPGDUMMYDAO_H

#include <QMap>
#include "qrpgdatabase.h"

namespace QRPGDao {
namespace Impl {

class QRPGDummyDao : public QRPGDao::QRPGDatabase
{
public:
    friend QRPGDao::QRPGDatabase *QRPGDao::newDao(QRPGDao::DaoType daoType);
    ~QRPGDummyDao();

private:
    QRPGDummyDao();
    QMap<QString, QRPGDao::QRPGProject *> openProjects;
    QMap<QString, QRPGDao::QRPGProject *> allProjects;

    // QRPGDatabase interface
public:
    QRPGDao::QRPGProject *createNewProject(const QDir &projectLocationDir, QString projectTitle, QString gameTitle);
    QRPGDao::QRPGProject *openProjectDir(QString projectDirURI);
    void closeProject(QString projectDirURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGDUMMYDAO_H
