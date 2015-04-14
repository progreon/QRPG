#include "qrpgdatabase.h"
#include "impl/qrpgdummydao.h"
#include "impl/qrpgfiledao.h"
#include "model/qrpgproject.h"

namespace QRPGDao {

QRPGDatabase *newDao(DaoType daoType)
{
    if (daoType == FILE) {
        return new QRPGDao::Impl::QRPGFileDao();
    } else {
        return new QRPGDao::Impl::QRPGDummyDao();
    }

    return NULL;
}

QRPGProject *QRPGDatabase::newProject(QString projectFolderURI, QString projectTitle, QString gameTitle)
{
    return new QRPGProject(this, projectFolderURI, projectTitle, gameTitle);
}

} // namespace QRPGDao

