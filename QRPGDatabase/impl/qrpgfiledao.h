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
    QRPGDao::QRPGProject *createNewProject(QString projectFolderURI, QString projectTitle, QString gameTitle);
    QRPGDao::QRPGProject *openProjectFolder(QString projectFolderURI);
    void closeProject(QString projectFolderURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGFILEDAO_H
