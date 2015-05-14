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
    QRPGDao::QRPGProject *createNewProject(const QDir &projectLocationDir, const QString &projectTitle, const QString &gameTitle);
    QRPGDao::QRPGProject *openDummyProject();
    QRPGDao::QRPGProject *openProjectDir(const QString &projectDirURI);
    void closeProject(const QString &projectDirURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGDUMMYDAO_H
