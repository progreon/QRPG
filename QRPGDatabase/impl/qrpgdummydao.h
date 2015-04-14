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
    QRPGDao::QRPGProject *createNewProject(QString projectFolderURI, QString projectTitle, QString gameTitle);
    QRPGDao::QRPGProject *openProjectFolder(QString projectFolderURI);
    void closeProject(QString projectFolderURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGDUMMYDAO_H
