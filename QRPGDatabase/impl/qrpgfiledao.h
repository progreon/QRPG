#ifndef QRPGDAO_IMPL_QRPGFILEDAO_H
#define QRPGDAO_IMPL_QRPGFILEDAO_H

#include <QMap>
#include "qrpgdatabase.h"

namespace QRPGDao {
namespace Impl {

class QRPGFileDao : public QRPGDao::QRPGDatabase
{
public:
    friend QRPGDao::QRPGDatabase *QRPGDao::newDao(QRPGDao::DaoType daoType);
    ~QRPGFileDao();

private:
    QRPGFileDao();
    QMap<QString, QRPGDao::QRPGProject *> openProjects;

    // QRPGDatabase interface
public:
    QRPGDao::QRPGProject *createNewProject(const QDir &projectLocationDir, QString projectTitle, QString gameTitle);
    QRPGDao::QRPGProject *openProjectDir(QString projectDirURI);
    void closeProject(QString projectDirURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGFILEDAO_H
