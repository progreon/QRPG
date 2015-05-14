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

//    return NULL;
}

QRPGProject *QRPGDatabase::newProject(const QString &projectDirURI, const QString &projectTitle, const QString &gameTitle)
{
    return new QRPGProject(this, projectDirURI, projectTitle, gameTitle);
}

void QRPGDatabase::setProjectTileSize(QRPGProject *project, int tileSize)
{
    if (project != NULL && tileSize != 0) {
        project->setTileSize(tileSize);
    }
}

} // namespace QRPGDao

